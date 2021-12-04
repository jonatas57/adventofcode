{- stack script --resolver lts-14.20 -}
module Main where

parse :: String -> Int
parse s = sum $ map fst $ filter (('1' ==) . snd) $ zip [2 ^ i | i <- [0..]] $ reverse s

task1 :: [String] -> Int
task1 _ = 0

task2 :: [String] -> Int
task2 _ = 0

main :: IO ()
main = do
  input <- fmap lines getContents
  putStrLn "Task 1: "
  print $ task1 input
  putStrLn "Task 2: "
  print $ task2 input

