{- stack script --resolver lts-14.20 
--package split  -}
module Main where

import Data.List.Split (splitOn)
import Data.List (sort)

task1 :: [[Int]] -> Int
task1 = maximum . map sum

task2 :: [[Int]] -> Int
task2 = sum . take 3 . reverse . sort . map sum

main :: IO ()
main = do
  input <- fmap (map (map read) . splitOn [""] . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input
