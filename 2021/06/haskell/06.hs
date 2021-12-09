{- stack script --resolver lts-14.20 
--package split
-}
module Main where

import Data.List
import Data.List.Split

parse :: String -> [Int]
parse = map read . splitOn ","

mulV :: [Int] -> [Int] -> [Int]
mulV = zipWith (*)

sumV :: [Int] -> [Int] -> [Int]
sumV = zipWith (+)

mulM :: [[Int]] -> [[Int]] -> [[Int]]
mulM a b = [[sum $ zipWith (*) ar bc | bc <- (transpose b)] | ar <- a]

mulMV :: [[Int]] -> [Int] -> [Int]
mulMV m v = map (sum . mulV v) m

xp :: [[Int]] -> Int -> [[Int]]
xp b 1                  = b
xp b e | e `mod` 2 == 0 = c
       | otherwise      = mulM c b
  where
    c' = xp b $ div e 2
    c  = mulM c' c'

m :: [[Int]]
m = [[0,1,0,0,0,0,0,0,0],[0,0,1,0,0,0,0,0,0],[0,0,0,1,0,0,0,0,0],[0,0,0,0,1,0,0,0,0],[0,0,0,0,0,1,0,0,0],[0,0,0,0,0,0,1,0,0],[1,0,0,0,0,0,0,1,0],[0,0,0,0,0,0,0,0,1],[1,0,0,0,0,0,0,0,0]]

task1 :: [Int] -> Int
task1 v = sum $ mulMV (xp m 80) v

task2 :: [Int] -> Int
task2 v = sum $ mulMV (xp m 256) v

main :: IO ()
main = do
  input <- fmap parse getContents
  let cnt = [length $ filter (==x) input | x <- [0..8]]
  print $ mulMV (xp m 2) cnt
  putStr "Task 1: "
  print $ task1 cnt
  putStr "Task 2: "
  print $ task2 cnt

