{- stack script
 --resolver lts-14.20
 --package vector
 -}
module Main where

import Prelude hiding (Left, Right)
import Data.Maybe
import qualified Data.Vector as V
import qualified Data.Set as S
import qualified Data.Map as M

data Map = Map {
  mat :: V.Vector (V.Vector Char),
  h   :: Int,
  w   :: Int
} deriving Show
type Pos = (Int, Int)

fromMatrix :: [String] -> Map
fromMatrix ss@(s:_) = Map (V.fromList $ map V.fromList ss) (length ss) $ length s 

(!?) :: Map -> (Int, Int) -> Maybe Char
m !? (x, y) = (mat m) V.!? x >>= (V.!? y)

data Dir = Up | Right | Down | Left deriving (Enum, Eq, Ord, Show)

data State = State Map Pos Dir deriving Show

getState :: Map -> State
getState m = State (Map (m' V.// [(x, (m' V.! x) V.// [(y, '.')])]) h w) (x, y) Up
  where
    (Map m' h w) = m
    (x, y)       = head $ filter ((/= -1) . snd) $ zip [0..] $ map find $ V.toList m'

    find :: V.Vector Char -> Int
    find v | null z    = -1
           | otherwise = fst $ head z
      where
        z = filter ((=='^') . snd) $ zip [0..] $ V.toList v

walk :: Pos -> Dir -> Pos
walk (x, y) Up    = (x - 1, y)
walk (x, y) Down  = (x + 1, y)
walk (x, y) Left  = (x, y - 1)
walk (x, y) Right = (x, y + 1)

next :: Dir -> Dir
next dir = toEnum $ (fromEnum dir + 1) `mod` 4

go :: State -> State
go (State m pos dir) | fromMaybe '.' (m !? pos') == '#' = State m pos $ next dir
                     | otherwise                        = State m pos' dir
  where
    (Map m' h w) = m
    pos'@(x, y)  = walk pos dir

task1 st = length $ S.toList $ S.fromList $ task1' st
  where
    (State _ pos d)                        = st
    st'@(State m@(Map mat h w) (x, y) dir) = go st

    task1' st | x < 0 || x >= h || y < 0 || y >= w = [pos]
              | d == dir                           = pos : task1' st'
              | otherwise                          = task1' st'
      where
        (State _ pos d)                        = st
        st'@(State m@(Map mat h w) (x, y) dir) = go st


task2 st = length $ filter (task2' S.empty) [State (Map (mat V.// [(a, (mat V.! a) V.// [(b, '#')])]) h w) (x, y) dir | (a, b) <- S.toList $ S.fromList $ task1' st]
  where
    openPos                                = [(x, y) | x <- [0..h - 1], y <- [0..w - 1], mat V.! x V.! y == '.']
    (State _ pos d)                        = st
    st'@(State m@(Map mat h w) (x, y) dir) = go st

    task1' st | x < 0 || x >= h || y < 0 || y >= w = [pos]
              | d == dir                           = pos : task1' st'
              | otherwise                          = task1' st'
      where
        (State _ pos d)                        = st
        st'@(State m@(Map mat h w) (x, y) dir) = go st

    task2' vis st | x < 0 || x >= h || y < 0 || y >= w = False
                  | S.member (pos, dir) vis            = True
                  | otherwise                          = task2' vis' st'
      where
        vis'                                    = S.insert (pos, dir) vis
        (State _ pos dir)                       = st
        st'@(State m@(Map mat h w) (x, y) ndir) = go st

main :: IO ()
main = do
  input <- fmap (getState . fromMatrix . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input
