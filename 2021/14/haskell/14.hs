{- stack script --resolver lts-14.20 
 --package split
 --package containers
-}
module Main where

import Data.List.Split
import qualified Data.Map as M

nTimes :: Int -> (a -> a) -> (a -> a)
nTimes 0 _ = id
nTimes 1 f = f
nTimes n f = f . nTimes (n - 1) f

parse :: [String] -> M.Map String Char
parse ss = parse' M.empty ss
  where
    parse' m []     = m
    parse' m (x:xs) = parse' (M.alter (\x -> Just $ head c) s m) xs
      where
        [s, c] = splitOn " -> " x

apply :: M.Map String Char -> M.Map String Int -> M.Map String Int
apply m cnt = foldr f M.empty $ M.assocs cnt
  where
    f :: (String, Int) -> M.Map String Int -> M.Map String Int
    f  ([x]     , qtd) ans = M.insertWith (+) (x :     []) qtd $ ans
    f ~(s@[x, y], qtd) ans = M.insertWith (+) (x : c : []) qtd $ M.insertWith (+) (c : y : []) qtd $ M.insertWith (+) (c : []) qtd ans
      where
        c = m M.! s

getAns :: M.Map String Int -> Int
getAns m = (foldl1 max m') - (foldl1 min m')
  where
    m' = M.filterWithKey (\k _ -> null $ tail k) m

count :: String -> M.Map String Int
count []       = M.empty
count [x]      = M.insertWith (+) (x : []) 1 $ M.empty
count (x:y:xs) = M.insertWith (+) (x : y : []) 1 $ M.insertWith (+) (x : []) 1 $ count $ y : xs

task1 :: M.Map String Char -> String -> Int
task1 m s = getAns $ nTimes 10 (apply m) $ count s

task2 :: M.Map String Char -> String -> Int
task2 m s = getAns $ nTimes 40 (apply m) $ count s

main :: IO ()
main = do
  input <- fmap lines getContents
  let poly = head input
      ins  = parse $ tail $ tail input
  putStr "Task 1: "
  print $ task1 ins poly
  putStr "Task 2: "
  print $ task2 ins poly

