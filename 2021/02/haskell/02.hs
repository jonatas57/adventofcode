{- stack script --resolver lts-14.20 
--package split
-}
module Main where

import Data.List.Split

data Op = Forward Int | Down Int | Up Int deriving Show

parse :: String -> Op
parse s | op == "forward" = Forward x
        | op == "down"    = Down x
        | otherwise       = Up x
  where
    [op, xstr] = splitOn " " s
    x = read xstr :: Int

task1 :: [Op] -> (Int, Int)
task1 xs = foldl apply (0, 0) xs
  where
    apply (pos, dep) (Forward x) = (pos + x, dep)
    apply (pos, dep) (Down x)    = (pos, dep + x)
    apply (pos, dep) (Up x)      = (pos, dep - x)

removeLast :: (a, a, a) -> (a, a)
removeLast (x, y, _) = (x, y)

task2 :: [Op] -> (Int, Int)
task2 xs = removeLast $ foldl apply (0, 0, 0) xs
  where
    apply (pos, dep, aim) (Forward x) = (pos + x, dep + aim * x, aim)
    apply (pos, dep, aim) (Down x)    = (pos, dep, aim + x)
    apply (pos, dep, aim) (Up x)      = (pos, dep, aim - x)

main :: IO ()
main = do
  input <- fmap (map parse . lines) getContents
  putStr "Task 1: " 
  print $ uncurry (*) $ task1 input
  putStr "Task 2: "
  print $ uncurry (*) $ task2 input

