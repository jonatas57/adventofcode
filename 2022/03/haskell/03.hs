{- stack script --resolver lts-14.20 -}
module Main where

import Data.Char (ord, isLower)
import Data.List (sort, nub)

type Item = Char

inter :: String -> String -> String
inter a b = inter' a' b'
  where
    a' = nub $ sort a
    b' = nub $ sort b
    inter' :: String -> String -> String
    inter' []     _                  = []
    inter' _      []                 = []
    inter' (x:xs) (y:ys) | x < y     = inter' xs (y:ys)
                         | x > y     = inter' (x:xs) ys
                         | otherwise = x : inter' xs ys

priority :: Char -> Int
priority c | isLower c = ord c - ord 'a' + 1
           | otherwise = ord c - ord 'A' + 27

task1 :: [String] -> Int
task1 []     = 0
task1 (x:xs) = (priority $ head $ inter a b) + task1 xs
  where
    (a, b) = splitAt hl x
    hl     = flip div 2 $ length x

task2 :: [String] -> Int
task2 [] = 0
task2 (a:b:c:xs) = (priority $ head $ inter a $ inter b c) + task2 xs

main :: IO ()
main = do
  input <- fmap lines getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input
