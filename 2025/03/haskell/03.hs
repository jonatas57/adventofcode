{- stack script --resolver lts-14.20 -}
module Main where

import Data.Char (ord)

task1 input = sum $ map (solve 0) input
  where
    solve :: Int -> [Int] -> Int
    solve m [x]    = 10 * m + x
    solve m (x:xs) = max v $ solve m' xs
      where
        v  = 10 * m + x
        m' = max x m

task2 input = sum $ map (last . solve 12) $ input
  where
    solve x cs = solve' x empty cs
      where
        empty = flip replicate 0 $ length cs

    solve' 0 as cs = as
    solve' x as cs = solve' (x - 1) (apply 0 as 0 cs) cs

    apply _ _ _ [] = []
    apply a' (a:as) b (c:cs) = b' : apply a as b' cs
      where
        b' = max b $ 10 * a' + c

main :: IO ()
main = do
  input <- flip fmap getContents $ map (map (\c -> ord c - ord '0')) . lines
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

