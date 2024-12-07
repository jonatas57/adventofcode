{- stack script --resolver lts-14.20 -}
module Main where

import Data.List

findXmas :: String -> Int
findXmas s = findXmas' "XMAS" s
  where
    findXmas' :: String -> String -> Int
    findXmas' _      []       = 0
    findXmas' "S"    ('S':s') = 1 + findXmas' "XMAS" s'
    findXmas' (x:xs)   (c:cs) | x == c    = findXmas' xs cs
                              | c == 'X'  = findXmas' "MAS" cs
                              | otherwise = findXmas' "XMAS" cs

getVertical :: [String] -> [String]
getVertical ([]:_) = []
getVertical ss     = map head ss : getVertical (map tail ss)

getDiagonal1 :: [String] -> [String]
getDiagonal1 ss = init $ getDiagonal 1 ss
  where
    getDiagonal _ []  = []
    getDiagonal x ss  = diag : getDiagonal (x + 1) ss'' 
      where
        ss'    = dropWhile null ss
        prefix = take x ss'
        suffix = drop x ss'
        ss''   = map tail prefix ++ suffix
        diag   = map head prefix

getDiagonal2 :: [String] -> [String]
getDiagonal2 = reverse . getDiagonal1 . reverse

task1 :: [String] -> Int
task1 input = h + v + d1 + d2
  where
    count :: [String] -> Int
    count ss = sum (map findXmas ss) + sum (map findXmas (map reverse ss))

    h  = count input
    v  = count $ getVertical input
    d1 = count $ getDiagonal1 input
    d2 = count $ getDiagonal2 input

findMas :: String -> [Int]
findMas s = findMas' "MAS" 0 s
  where
    findMas' :: String -> Int -> String -> [Int]
    findMas' _      _ []       = []
    findMas' "S"    p ('S':s') = (p - 1) : findMas' "MAS" (p + 1) s'
    findMas' (x:xs) p   (c:cs) | x == c    = findMas' xs (p + 1) cs
                               | c == 'M'  = findMas' "AS" (p + 1) cs
                               | otherwise = findMas' "MAS" (p + 1) cs

enumerateFinds conv f gd ss = map conv . concat . filter (not . null) . zipWith f [0..] $ map findMas $ gd ss

task2 input = inter d1 d2
  where
    n   = length input
    m   = length $ head input
    d1l = enumerateFinds (\(x, y) -> (max  0 (x - n + 1) + y, min (m - 1)  x              - y)) (\a b -> map (a,) b)                getDiagonal1  input
    d1r = enumerateFinds (\(x, y) -> (min  x (n - 1)     - y, max  0      (x - m + 1)     + y)) (\a b -> map (a,) b) (map reverse . getDiagonal1) input
    d2l = enumerateFinds (\(x, y) -> (min  x (n - 1)     - y, min (m - 1) (n + m - 2 - x) - y)) (\a b -> map (a,) b)                getDiagonal2  input
    d2r = enumerateFinds (\(x, y) -> (max  0 (x - n + 1) + y, max  0      (m - 1 - x)     + y)) (\a b -> map (a,) b) (map reverse . getDiagonal2) input
    d1  = sort $ d1l ++ d1r
    d2  = sort $ d2l ++ d2r

    inter :: [(Int, Int)] -> [(Int, Int)] -> Int
    inter [] _ = 0
    inter _ [] = 0
    inter (a:as) (b:bs) | a == b    = 1 + inter as bs
                        | a <  b    = inter as (b:bs)
                        | otherwise = inter (a:as) bs

main :: IO ()
main = do
  input <- fmap lines getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input


