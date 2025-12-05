{- stack script --resolver lts-14.20 -}
module Main where

import Data.List

split :: Eq a => a -> [a] -> ([a], [a])
split x xs = (takeWhile (/= x) xs, drop 1 $ dropWhile (/= x) xs)

task1 rngs ings = solve (sort rngs) $ sort ings
  where
    solve [] _ = 0
    solve _  [] = 0
    solve rs@((l, r):xs) is@(y:ys) | y < l     = solve rs ys
                                   | y <= r    = 1 + solve rs ys
                                   | otherwise = solve xs is

task2 input = solve (-1) $ sort input
  where
    solve _ [] = 0
    solve last ((l, r):xs) | l > last + 1 = r - l + 1 + solve r xs
                           | r <= last    = solve last xs
                           | otherwise    = r - last + solve r xs

apply :: (a -> b) -> (c -> d) -> (a, c) -> (b, d)
apply f g (x, y) = (f x, g y)

main :: IO ()
main = do
  (rngs :: [(Int, Int)], ings :: [Int]) <- flip fmap getContents $ apply (map (apply read read . split '-')) (map read) . split [] . lines
  putStr "Task 1: "
  print $ task1 rngs ings
  putStr "Task 2: "
  print $ task2 rngs

