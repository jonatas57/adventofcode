{- stack script
--resolver lts-14.20 
--package parsec -}
module Main where

import Text.Parsec
import Text.Parsec.Text

type Interval = (Int, Int)
type Assignment = (Interval, Interval)
type Parser = Parsec String ()

parseInt :: Parsec String () Int
parseInt = many digit >>= return . read

parseInterval :: Parsec String () Interval
parseInterval = sepBy parseInt (char '-') >>= return . mkInterval
  where
    mkInterval [a, b] = (a, b)

parseAssignment :: Parsec String () Assignment
parseAssignment = sepBy parseInterval (char ',') >>= return . mkAssignment
  where
    mkAssignment [a, b] = (a, b)

parseInput :: [String] -> [Assignment]
parseInput []     = []
parseInput (x:xs) = case runParser parseAssignment () "" x of
  Left  _ -> []
  Right a -> a : parseInput xs

task1 :: [Assignment] -> Int
task1 xs = sum [if inside a b then 1 else 0 | (a, b) <- xs]
  where
    inside (a, b) (c, d) = (a <= c && d <= b) || (c <= a && b <= d)

task2 :: [Assignment] -> Int
task2 xs = sum [if overlap a b then 1 else 0 | (a, b) <- xs]
  where
    overlap (a, b) (c, d) = max a c <= min b d

main :: IO ()
main = do
  input <- fmap (parseInput . lines) getContents
  print $ length input
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

