{- stack script --resolver lts-14.20 
 --package split -}
module Main where

import Data.List       ( nub, sort )
import Data.List.Split ( splitOn )

type Pos = (Int, Int)
data Fold = X Int | Y Int deriving Show

apply' :: Int -> Int -> Int
apply' v x | x > v     = v + v - x
           | otherwise = x

apply :: Fold -> Pos -> Pos
apply (X v) (x, y) = (apply' v x, y)
apply (Y v) (x, y) = (x, apply' v y)

task1 :: [Pos] -> [Fold] -> Int
task1 ps ~(f:fs) = length $ nub $ map (apply f) ps

task2 :: [Pos] -> [Fold] -> String
task2 ps fs = foldl1 (\a b -> a ++ "\n" ++ b) [[if (x, y) `elem` rs then '#' else '.' | x <- [0..r]] | y <- [0..b]]
  where
    rs = nub $ sort $ foldl (flip (map . apply)) ps fs
    xs = map fst rs
    ys = map snd rs
    r  = foldl1 max xs
    b  = foldl1 max ys


parsePoints :: [String] -> [Pos]
parsePoints ss = map (toTuple . splitOn ",") ss
  where
    toTuple [x, y] = (read x, read y)

parseFolds :: [String] -> [Fold]
parseFolds ss = map (parse . splitOn "=" . last . splitOn " ") ss
  where
    parse [ax, v] | ax == "x" = X $ read v
                  | otherwise = Y $ read v

main :: IO ()
main = do
  input <- fmap (splitOn [""] . lines) getContents
  let ps = parsePoints $ head input
      fs = parseFolds  $ last input
  putStr "Task 1: "
  print $ task1 ps fs
  putStrLn "Task 2: "
  putStrLn $ task2 ps fs

