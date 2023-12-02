{- stack script --resolver lts-14.20 -}
module Main where

import Data.Char

fal :: [a] -> [a]
fal xs = [head xs, last xs]

task1 :: [String] -> Int
task1 xs = sum $ map (read . fal . filter isDigit) xs

--------------------------------------------------------------------------------

data Zipper = Zip String String deriving Show

createZipper :: String -> Zipper
createZipper = Zip []

reset :: Zipper -> Zipper
reset (Zip []     xs) = Zip [] xs
reset (Zip (l:ls) rs) = reset $ Zip ls $ l : rs

type State = (Zipper, Int)
nums :: [State]
nums = flip zip [1..] $ map createZipper ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]

go :: Char -> Zipper -> (Zipper, Bool)
go c z@(Zip ls [])                 = (z, False)
go c z@(Zip ls (r:rs)) | c == r    = (Zip (r:ls) rs, null rs)
                       | null ls   = (z, False)
                       | otherwise = go c $ reset z

apply :: Char -> [State] -> [Int] -> ([State], [Int])
apply _    []  xs = ([], xs)
apply c ((z, val):zs) xs = f (z'', val) $ apply c zs xs'
  where
    (z', ok) = go c z
    z'' | ok        = reset z'
        | otherwise = z'
    xs' | ok        = val : xs
        | otherwise = xs

    f :: State -> ([State], [Int]) -> ([State], [Int])
    f z (zs, xs) = (z : zs, xs)

parse :: String -> [State] -> [Int]
parse cs zs = reverse $ snd $ parse' cs zs []
  where
    parse' :: String -> [State] -> [Int] -> ([State], [Int])
    parse'    []  zs xs = (zs, xs)
    parse' (c:cs) zs xs | isDigit c = parse' cs (map (\(z, x) -> (reset z, x)) zs) $ flip (:) xs $ ord c - ord '0'
                        | otherwise = parse' cs zs' xs'
      where
        (zs', xs') = apply c zs xs

task2 xs = sum $ map (foldl mount 0 . fal . flip parse nums) xs
  where
    mount :: Int -> Int -> Int
    mount x y = 10 * x + y

--------------------------------------------------------------------------------

main :: IO ()
main = do
  input <- fmap (filter (not . null) . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

