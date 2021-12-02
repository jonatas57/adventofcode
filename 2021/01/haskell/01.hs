{-stack script
--resolver lts-14.20
-}

module Main where

readInt :: String -> Int
readInt s = read s :: Int

task1 :: [Int] -> Int
task1 input = length $ filter (\x -> x) $ map (uncurry (\x y -> y > x)) $ zip input $ tail input

task2 :: [Int] -> Int
task2 input = length $ filter (\x -> x) $ map (uncurry (\x y -> y > x)) $ zip input $ drop 3 input

main :: IO ()
main = do
  input <- fmap (map readInt . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

