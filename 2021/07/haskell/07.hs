{- stack script --resolver lts-14.20 
--package split
-}
module Main where

import Data.List
import Data.List.Split

parse :: String -> [Int]
parse = map read . splitOn ","

getMode :: [Int] -> Int
getMode []     = 0
getMode [x]    = x
getMode [x, y] = x
getMode xs     = getMode $ init $ tail xs

task1 :: [Int] -> Int
task1 xs = sum $ zipWith (\x y -> abs $ x - y) xs' [mode,mode..]
  where
    xs'  = sort xs
    mode = getMode xs'

sum1toN :: Int -> Int
sum1toN n = flip div 2 $ n * (n + 1)

calc :: [Int] -> Int -> Int
calc xs pos = sum $ [sum1toN $ abs $ x - pos | x <- xs]

task2 :: [Int] -> Int
task2 xs = foldl1' min $ map (calc xs) [(foldl1' min xs)..(foldl1' max xs)]

main :: IO ()
main = do
  input <- fmap parse getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

