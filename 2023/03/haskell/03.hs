{- stack script --resolver lts-14.20 
                --package containers-}
module Main where

import Data.Char hiding (isSymbol, isNumber)
import qualified Data.Map as M
import Data.Maybe
import Data.List

data Engine = Number Int Int | Symbol Char deriving (Eq, Show, Ord)

isGear :: Engine -> Bool
isGear (Symbol '*') = True
isGear          _   = False

isSymbol :: Engine -> Bool
isSymbol (Symbol _) = True
isSymbol         _  = False

isNumber :: Engine -> Bool
isNumber (Number _ _) = True
isNumber           _  = False

fromNumber :: Engine -> Int
fromNumber (Number _ x) = x

getAdjPos :: (Int, Int) -> [(Int, Int)]
getAdjPos (x, y) = [(a + x, b + y) | a <- [-1..1], b <- [-1..1], a /= 0 || b /= 0]

insertN :: Ord k => [k] -> a -> M.Map k a -> M.Map k a
insertN []       _ m = m
insertN (k:ks) val m = insertN ks val $ M.insert k val m

changeKey :: (Ord a, Ord c) => (a -> b -> c) -> b -> M.Map a v -> M.Map c v
changeKey f x m = M.fromList $ map (\(k, v) -> (f k x, v)) $ M.toList m

parse :: [String] -> M.Map (Int, Int) Engine
parse ss = foldl M.union M.empty $ zipWith (changeKey $ flip (,)) [0..] $ parse' 0 ss
  where
    parse' _     []  = []
    parse' id (s:ss) = m : parse' id' ss
      where
        (id', m) = parseRow id s

parseRow :: Int -> String -> (Int, M.Map Int Engine)
parseRow startId s = parseRow' startId M.empty (-1) 0 0 s
  where
    parseRow' :: Int -> M.Map Int Engine -> Int -> Int -> Int -> String -> (Int, M.Map Int Engine)
    parseRow' id m st at acc []    = (id, m)
    parseRow' id m st at acc (c:s) | isDigit c = parseRow' id m st (at + 1) (acc * 10 + ord c - ord '0') s
                                   | acc == 0  = parseRow' id m' at (at + 1) acc s
                                   | otherwise = parseRow' (id + 1) (insertN [st + 1..at - 1] (Number id acc) m') at (at + 1) 0 s
      where
        m' | c /= '.'  = M.insert at (Symbol c) m
           | otherwise = m

--------------------------------------------------------------------------------

getNeighbours :: M.Map (Int, Int) Engine -> (Int, Int) -> [Engine]
getNeighbours m pos = map (fromMaybe (Number 0 0)) $ filter isJust $ map (flip M.lookup m) $ getAdjPos pos

task1 :: M.Map (Int, Int) Engine -> Int
task1 m = sum $ map (fromNumber . fst) $ M.toList $ M.filter (not . null) symCount
  where
    adjSymbols pos = nub $ filter isSymbol $ getNeighbours m pos
    symCount = foldl (M.unionWith (++)) M.empty [M.fromList [(e, adjSymbols p)] | (p, e) <- M.toList m, isNumber e]

task2 m = sum $ map (foldl (*) 1) $ filter (\ns -> length ns == 2) $ map adjNumbers gearPos
  where
    gearPos = map fst $ M.toList $ M.filter isGear m
    adjNumbers pos = map fromNumber $ nub $ map (fromMaybe (Symbol ' ')) $ filter (\x -> isJust x) [m M.!? p | p <- getAdjPos pos]

main :: IO ()
main = do
  input <- flip fmap getContents $ parse . map (++ ".") . lines
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

