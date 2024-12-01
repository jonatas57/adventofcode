{- stack script --resolver lts-14.20 -}
module Main where

import Data.List

parse :: [[Int]] -> ([Int], [Int])
parse [] = ([], [])
parse (x:xs) = (p : a, q : b)
  where
    (a, b) = parse xs
    [p, q] = x

task1 :: ([Int], [Int]) -> Int
task1 (a, b) = sum $ zipWith (\x y -> abs $ x - y) a' b'
  where
    a' = sort a
    b' = sort b

task2 :: ([Int], [Int]) -> Int
task2 (a, b) = task2' a' b'
  where
    a' = sort a
    b' = sort b

    task2' :: [Int] -> [Int] -> Int
    task2' []  _ = 0
    task2'  _ [] = 0
    task2'  a  b | ha == hb  = cnta * cntb * ha + task2' a' b'
                 | ha  < hb  = task2' a' b
                 | otherwise = task2' a  b'
      where
        ha   = head a
        hb   = head b
        a'   = dropWhile (== ha) a
        b'   = dropWhile (== hb) b
        cnta = length $ takeWhile (== ha) a
        cntb = length $ takeWhile (== hb) b

main :: IO ()
main = do
  input <- fmap (parse . map (map read . words) . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input


