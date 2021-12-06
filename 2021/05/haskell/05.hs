{- stack script --resolver lts-14.20
--package containers
--package split
-}
module Main where

import Data.List
import Data.List.Split
import qualified Data.Map as M

isHorOrVer :: (Int, Int) -> (Int, Int) -> Bool
isHorOrVer (a, b) (c, d) = a == c || b == d

genInterval :: Int -> Int -> [Int]
genInterval a b | a == b    = [a,a..]
                | a <  b    = [a..b]
                | otherwise = [a,a - 1..b]

genLine :: (Int, Int) -> (Int, Int) -> [(Int, Int)]
genLine (a, b) (c, d) = zip (genInterval a c) (genInterval b d)

parse :: String -> ((Int, Int), (Int, Int))
parse s = ((a, b), (c, d))
  where
    [p, q] = splitOn " -> " s
    [a, b] = map read $ splitOn "," p
    [c, d] = map read $ splitOn "," q

updateOrInsert :: Maybe Int -> Maybe Int
updateOrInsert Nothing  = Just 1
updateOrInsert (Just x) = Just $ x + 1

task1 :: [((Int, Int), (Int, Int))] -> Int
task1 xs = length $ filter (\(x, y) -> y > 1) items
  where
    items  = M.toList m
    m      = foldl (flip $ M.alter updateOrInsert) M.empty points
    points = concat $ map (uncurry genLine) $ filter (uncurry isHorOrVer) xs

task2 :: [((Int, Int), (Int, Int))] -> Int
task2 xs = length $ filter (\(x, y) -> y > 1) items
  where
    items  = M.toList m
    m      = foldl (flip $ M.alter updateOrInsert) M.empty points
    points = concat $ map (uncurry genLine) xs

main :: IO ()
main = do
  input <- fmap (map parse . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

