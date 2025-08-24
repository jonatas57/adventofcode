{- stack script --resolver lts-14.20 -package container -}
module Main where

import Data.List
import qualified Data.Map as M

apply :: (a -> a -> a) -> (a, a) -> (a, a) -> (a, a)
apply f (x1, y1) (x2, y2) = (f x1 x2, f y1 y2)

parse :: [String] -> [[(Int, Int)]]
parse input = map snd $ M.toList $ compress 0 $ map (parseLine 0) input
  where
    parseLine :: Int -> String -> [(Char, Int)]
    parseLine _   []       = []
    parseLine pos ('.':xs) = parseLine (pos + 1) xs
    parseLine pos (  x:xs) = (x, pos) : parseLine (pos + 1) xs

    compress :: Int -> [[(Char, Int)]] -> M.Map Char [(Int, Int)]
    compress   _ [] = M.empty
    compress pos (l:ls) = compressLine (compress (pos + 1) ls) pos l

    compressLine :: M.Map Char [(Int, Int)] -> Int -> [(Char, Int)] -> M.Map Char [(Int, Int)]
    compressLine acc x [] = acc
    compressLine acc x ((c, y):ys) = compressLine (M.insertWith (++) c [(x, y)] acc) x ys

check :: (Int, Int) -> (Int, Int) -> Bool
check (h, w) (x, y) = 0 <= x && x < w && 0 <= y && y < h

task1 :: [String] -> Int
task1 input = length $ nub $ filter (check (h, w)) $ concat [[apply (+) a $ apply (-) a b | a <- ant, b <- ant, a /= b] | ant <- input']
  where
    input' = parse input
    h = length input
    w = length $ head input

generateAntiNodes :: (Int, Int) -> (Int, Int) -> [(Int, Int)]
generateAntiNodes a b = a : generateAntiNodes b c
  where
    c = apply (+) b $ apply (-) b a


task2 input = length $ nub $ concat [concat [takeWhile (check (h, w)) $ generateAntiNodes a b | a <- ant, b <- ant, a /= b] | ant <- input']
  where
    input' = parse input
    h = length input
    w = length $ head input

main :: IO ()
main = do
  input <- fmap lines getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input


