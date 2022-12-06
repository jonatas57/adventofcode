{- stack script
--resolver lts-14.20
--package split -}
module Main where

import Data.Char (isDigit, isSpace)
import Data.List.Split (splitOn)

data Op = Move Int Int Int deriving Show

parseOp :: String -> Op
parseOp s = Move qtd (from - 1) (to - 1)
  where
    s'  = drop 5 s
    qtd = read $ takeWhile isDigit s'
    s'' = drop 6 $ dropWhile isDigit s'
    from = read $ takeWhile isDigit s''
    s''' = drop 4 $ dropWhile isDigit s''
    to = read $ takeWhile isDigit s'''

parseStacks :: [String] -> [String]
parseStacks xs = map (dropWhile isSpace . reverse . snd) $ filter (\(x, _) -> x `mod` 4 == 0) $ zip [-1..] $ parseStacks' (init xs) $ flip replicate [] $ length $ head xs
  where
    parseStacks' []     sts = sts
    parseStacks' (x:xs) sts = parseStacks' xs $ zipWith (:) x sts

modify :: (a -> a) -> Int -> [a] -> [a]
modify f 0 (x:xs) = f x : xs
modify f i (x:xs) = x : modify f (i - 1) xs

task1 :: [String] -> [Op] -> String
task1 sts []                 = map head sts
task1 sts ((Move q f t):ops) = flip task1 ops $ apply q f t sts
  where 
    apply :: Int -> Int -> Int -> [String] -> [String]
    apply 0 _ _ sts = sts
    apply x a b sts = apply (x - 1) a b $ modify (c:) b $ modify tail a sts
      where
        c = head $ sts !! a

task2 :: [String] -> [Op] -> String
task2 sts []                 = map head sts
task2 sts ((Move q f t):ops) = flip task2 ops $ apply q f t sts
  where
    apply :: Int -> Int -> Int -> [String] -> [String]
    apply q f t sts = modify (mv ++) t $ modify (drop q) f sts
      where
        mv = take q $ sts !! f

main :: IO ()
main = do
  [in1, in2] <- fmap (splitOn [""] . lines) getContents
  let sts = parseStacks in1
      ops = map parseOp in2
  putStr "Task 1: "
  putStrLn $ task1 sts ops
  putStr "Task 2: "
  putStrLn $ task2 sts ops

