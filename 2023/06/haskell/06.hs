{- stack script --resolver lts-14.20 
                --package split -}
module Main where

import Data.List.Split

bb :: Int -> Int -> (Int -> Int) -> Int -> Int
bb l r f d | l == r      = l
           | result <= d = bb (mid + 1) r f d
           | otherwise   = bb l mid f d
  where
    mid    = flip div 2 $ l + r
    result = f mid

calc :: Int -> Int -> Int
calc t x = x * (t - x)

solve :: Int -> Int -> Int
solve t d = t - 2 * x + 1
  where
    x = bb 0 (t `div` 2) (calc t) d

task1 :: [(Int, Int)] -> Int
task1 = product . map (uncurry solve)

task2 :: [(Int, Int)] -> Int
task2 input = uncurry solve input'
  where
    input' = (\(a, b) -> (read a, read b)) $ foldl (\(a, b) (c, d) -> (a ++ c, b ++ d)) ("", "") $ map (\(a, b) -> (show a, show b)) input

main :: IO ()
main = do
  [ts, ds] <- flip fmap getContents $ map (map read . tail . filter (not . null) . splitOn " ") . lines
  let input = zip ts ds
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

