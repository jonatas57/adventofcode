{- stack script --resolver lts-14.20
 --package containers -}
module Main where

import qualified Data.Map as M
import Data.Maybe

find :: Int -> String -> Int
find x s = find' M.empty x 1 1 s
  where 
    find' :: M.Map Char Int -> Int -> Int -> Int -> String -> Int
    find' last cnt start i (c:cs) | i - start' + 1 == cnt = i
                                  | otherwise             = find' last' cnt start' (i + 1) cs
      where
        start' = max start $ (+1) . fromMaybe (-1) $ M.lookup c last
        last'  = M.insert c i last

task1 :: String -> Int
task1 = find 4

task2 :: String -> Int
task2 = find 14

main :: IO ()
main = do
  input <- getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

