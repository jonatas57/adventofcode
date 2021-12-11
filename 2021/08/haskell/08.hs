{- stack script --resolver lts-14.20 
--package split
-}
module Main where

import Data.List
import Data.List.Split

task1 :: [([String], [String])] -> Int
task1 xs = length $ concatMap (filter (\x -> flip elem [2,3,4,7] $ length x) . snd) xs

evalDig :: [(String, Int)] -> [String] -> Int
evalDig dec ss = foldl (\x y -> 10 * x + y) 0 $ map conv ss
  where
    conv :: String -> Int
    conv s | null match = 0
           | otherwise  = snd $ head $ match
      where
        match = filter ((== s) . fst) dec

countEqual :: String -> String -> Int
countEqual   []       _      = 0
countEqual   _        []     = 0
countEqual s@(x:xs) t@(y:ys) | x == y    = countEqual xs ys + 1
                             | x <  y    = countEqual xs t
                             | otherwise = countEqual s ys

decode :: [String] -> [(String, Int)]
decode xs = zip [zer, one, two, thr, fou, fiv, six, sev, eig, nin] [0..]
  where
    zer = head $ filter (\x -> x /= six && x /= nin) le6
    one = head $ filter ((== 2) . length) xs
    two = head $ filter (\x -> x /= fiv && x /= thr) le5
    thr = head $ filter ((== 3) . countEqual sev) le5
    fou = head $ filter ((== 4) . length) xs
    fiv = head $ filter ((== 5) . countEqual six) le5
    six = head $ filter ((== 2) . countEqual sev) le6
    sev = head $ filter ((== 3) . length) xs
    eig = head $ filter ((== 7) . length) xs
    nin = head $ filter ((== 5) . countEqual thr) le6
    le5 = filter ((== 5) . length) xs
    le6 = filter ((== 6) . length) xs

task2 :: [([String], [String])] -> Int
task2 []     = 0
task2 (x:xs) = (evalDig table . snd) x + task2 xs
  where
    table = decode $ fst x

splitToTuple :: [String] -> ([String], [String])
splitToTuple ss = (map sort a, map sort b)
  where
    [a, b] = splitOn ["|"] ss

main :: IO ()
main = do
  input <- fmap (map splitToTuple . map (splitOn " ") . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

