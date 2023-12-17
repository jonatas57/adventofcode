{- stack script --resolver lts-14.20 
                --package split -}
module Main where

import Data.List.Split
import Data.List

type Map = [Int]
type Mapper = [Map]

parseSeeds :: String -> [Int]
parseSeeds s = map read $ tail $ splitOn " " s

parseMappers :: [String] -> [Mapper]
parseMappers ss = map (map (map read . splitOn " ") . tail) [s | s <- splitOn [""] ss, not $ null s]

parse :: [String] -> ([Int], [Mapper])
parse (s:ss) = (parseSeeds s, parseMappers ss)

apply :: Mapper -> Int -> Int
apply []     x = x
apply (m:ms) x | x' /= x   = x'
               | otherwise = apply ms x
  where
    x' = applyMap m x

applyMap :: Map -> Int -> Int
applyMap [a, b, c] x | b <= x && x < b + c = x - b + a
                     | otherwise           = x

task1 :: [Int] -> [Mapper] -> Int
task1 ss ms = minimum $ task1' ss ms
  where
    task1' :: [Int] -> [Mapper] -> [Int]
    task1' ss    []  = ss
    task1' ss (m:ms) = flip task1' ms $ flip map ss $ apply m

apply2 :: Mapper -> (Int, Int) -> [(Int, Int)]
apply2 []     x = [x]
apply2 (m:ms) x | snd x'' /= snd x = x'
                | otherwise        = init x' ++ apply2 ms x''
  where
    x'  = applyMap2 m x
    x'' = last x'

applyMap2 :: Map -> (Int, Int) -> [(Int, Int)]
applyMap2 [a, b, c] (l, r) = [(x, y) | (x, y) <- [(l, min r $ b - 1), (a - b + max l b, a - b + (min r $ b + c - 1)), (max l $ b + c, r)], x <= y]

task2 :: [Int] -> [Mapper] -> Int
task2 ss ms = fst $ minimum $ task2' ss' ms
  where
    ss' = pairs ss

    pairs :: [Int] -> [(Int, Int)]
    pairs []       = []
    pairs (x:y:xs) = (x, x + y - 1) : pairs xs

task2' :: [(Int, Int)] -> [Mapper] -> [(Int, Int)]
task2' ss    []  = ss
task2' ss (m:ms) = flip task2' ms $ sort $ flip concatMap ss $ apply2 m

main :: IO ()
main = do
  input <- flip fmap getContents lines
  let (seeds, mappers) = parse input
  putStr "Task 1: "
  let mappers' = flip map mappers $ sortBy (\[a, b, c] [d, e, f] -> compare [b, a, c] [e, d, f])
  print $ task1 seeds mappers'
  putStr "Task 2: "
  print $ task2 seeds mappers'

