{- stack script --resolver lts-14.20 
--package split
-}
module Main where

import Data.List.Split

data Bingo = Bingo [(Int, Int, Int)] [Int] [Int] Int deriving Show

mkBingo :: [[Int]] -> Bingo
mkBingo xs = Bingo tup [0,0,0,0,0] [0,0,0,0,0] s
  where
    s   = sum $ map sum xs
    tup = concat $ map (\(x, xs) -> [(x, a, b) | (a, b) <- xs]) $ zip [0..] $ map (zip [0..]) xs

parseList :: Char -> String -> [Int]
parseList ch = map read . filter (not . null) . splitOn (ch : "")

parseBingo :: [String] -> [Bingo]
parseBingo = map mkBingo . filter (not . null) . map (map (parseList ' ')) . splitOn [""]

mark :: Int -> Bingo -> Bingo
mark x bingo@(Bingo table row col s) | a == -1   = bingo
                                     | otherwise = Bingo table row' col' (s - x)
  where
    row' = take a row ++ [(row !! a) + 1] ++ drop (a + 1) row
    col' = take b col ++ [(col !! b) + 1] ++ drop (b + 1) col
    (a, b, _) = if null tup then (-1, -1, -1) else head tup
    tup = filter (\(_, _, c) -> c == x) table

isCompleted :: Bingo -> Bool
isCompleted (Bingo _ r c _) = any id $ map (not . null . (filter (==5))) [r, c]

firstNonZero :: [Int] -> Maybe Int
firstNonZero []                 = Nothing
firstNonZero (x:xs) | x == 0    = firstNonZero xs
                    | otherwise = Just x

calc :: Int -> Bingo -> Int
calc x (Bingo _ _ _ s) = x * s

task1 :: [Int] -> [Bingo] -> Int
task1 []     _     = -1
task1 (x:xs) bingo = case ans of 
  Nothing  -> task1 xs applied
  Just val -> val
  where
    ans     = firstNonZero $ map (calc x) cs
    applied = map (mark x) bingo
    cs      = filter isCompleted applied

lastNonZero :: [Int] -> Maybe Int
lastNonZero xs = firstNonZero $ reverse xs

task2 :: [Int] -> [Bingo] -> Int
task2 []     _     = -1
task2 (x:xs) bingo = case ans of 
  Nothing  -> task2 xs cs
  Just val -> val
  where
    applied = map (mark x) bingo
    cs      = filter (not . isCompleted) applied
    ans | null cs   = lastNonZero $ map (calc x) applied
        | otherwise = Nothing

main :: IO ()
main = do
  input <- fmap lines getContents
  let ns = parseList ',' $ head input
  let bs = parseBingo $ tail $ tail input
  putStr "Task 1: "
  print $ task1 ns bs
  putStr "Task 2: "
  print $ task2 ns bs

