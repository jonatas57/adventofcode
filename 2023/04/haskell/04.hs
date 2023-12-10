{- stack script --resolver lts-14.20 -}
module Main where

import Data.Char
import Data.List

data Card = Card [Int] [Int] deriving Show

splitOn :: Char -> String -> [String]
splitOn _     []  = []
splitOn ch (c:cs) | c == ch   = [] : splitOn ch cs
                  | otherwise = add c $ splitOn ch cs
  where
    add c [] = [c : []]
    add c (x:xs) = (c : x) : xs

parse :: String -> Card
parse s = Card (sort win) $ sort num
  where
    s' = drop 1 $ dropWhile (\c -> c /= ':') s
    [win, num] = map (map read . filter (not . null) . splitOn ' ') $ splitOn '|' s'

countWins :: Card -> Int
countWins (Card [] _) = 0
countWins (Card _ []) = 0
countWins (Card (x:xs) (y:ys)) | x < y     =     countWins $      Card xs $ y : ys
                               | x > y     =     countWins $ flip Card ys $ x : xs
                               | otherwise = 1 + countWins (Card xs ys)

points :: Int -> Int
points 0 = 0
points 1 = 1
points x = 2 * points (x - 1)

task1 :: [Card] -> Int
task1 = sum . map (points . countWins)

mapCount :: Int -> (a -> a) -> [a] -> [a]
mapCount 0 _ xs = xs
mapCount _ _ [] = []
mapCount n f (x:xs) = f x : mapCount (n - 1) f xs

task2 :: [Card] -> Int
task2 cs = sum $ run (replicate (length cs) 1) cs
  where
    run :: [Int] -> [Card] -> [Int]
    run    xs     []  = xs
    run (x:xs) (c:cs) = (:) x $ flip run cs $ mapCount wins (+ x) xs
      where
        wins = countWins c

main :: IO ()
main = do
  input <- flip fmap getContents $ map parse . lines
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

