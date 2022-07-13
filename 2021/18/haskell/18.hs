{- stack script --resolver lts-14.20 -}
module Main where

import Data.Char

splitWhile :: (a -> Bool) -> [a] -> ([a], [a])
splitWhile f xs = (takeWhile f xs, dropWhile f xs)

fst3 :: (a, b, c) -> a
fst3 (x, _, _) = x

doWhile :: (a -> (a, Bool)) -> a -> a
doWhile f x | cont      = doWhile f x'
            | otherwise = x'
  where
    (x', cont) = f x

--------------------------------------------------------------------------------

data Number = Value Int | Pair Number Number

instance Show Number where
  show (Value x)  = show x
  show (Pair l r) = '[' : show l ++ ',' : show r ++ "]"

magnitude :: Number -> Int
magnitude (Value x)  = x
magnitude (Pair l r) = 3 * magnitude l + 2 * magnitude r

(.+) :: Number -> Number -> Number
a .+ b = reduce $ Pair a b
infixl 6 .+

--------------------------------------------------------------------------------

parseNumber :: String -> Number
parseNumber = fst . parseNumber'

parseNumber' :: String -> (Number, String)
parseNumber' xs | head xs == '[' = (Pair l r, tail xs'')
                | otherwise      = parseValue xs
  where
    (l, xs' ) = parseNumber' $ tail xs
    (r, xs'') = parseNumber' $ tail xs'

parseValue :: String -> (Number, String)
parseValue xs = (Value $ read num, xs')
  where
    (num, xs') = splitWhile isDigit xs

--------------------------------------------------------------------------------

sumL :: Int -> Number -> Number
sumL 0 n          = n
sumL x (Value y)  = Value $ x + y
sumL x (Pair l r) = Pair (sumL x l) r

sumR :: Int -> Number -> Number
sumR 0 n          = n
sumR x (Value y)  = Value $ x + y
sumR x (Pair l r) = Pair l (sumR x r)

explode' :: Int -> Number -> (Number, Bool, Int, Int)
explode' _ v@(Value _)                  = (v, False, 0, 0)
explode' 4 p@(Pair (Value l) (Value r)) = (Value 0, True, l, r)
explode' _ p@(Pair (Value l) (Value r)) = (p, False, 0, 0)
explode' d (Pair l r) = (Pair (sumR sl2 l') (sumL sr1 r'), okl || okr, sl1, sr2)
  where
    (l', okl, sl1, sr1)             = explode' (d + 1) l
    (r', okr, sl2, sr2) | okl       = (r, False, 0, 0)
                        | otherwise = explode' (d + 1) r

--------------------------------------------------------------------------------

explode :: Number -> Number
explode n | cont      = explode n'
          | otherwise = n'
  where
    (n', cont, _, _) = explode' 0 n

split :: Number -> (Bool, Number)
split (Pair l r)  | okl       = (okl, Pair l' r )
                  | otherwise = (okr, Pair l  r')
  where
    (okl, l') = split l
    (okr, r') = split r
split v@(Value x) | x >= 10 = (True, Pair (Value l) (Value r))
                  | otherwise = (False, v)
  where
    l = div x 2
    r = x - l

reduce :: Number -> Number
reduce n | again     = reduce n'
         | otherwise = n'
  where
    (again, n') = split $ explode n

--------------------------------------------------------------------------------

task1 :: [Number] -> Int
task1 = magnitude . foldl1 (.+)

task2 :: [Number] -> Int
task2 xs = maximum [magnitude $ a .+ b | a <- xs, b <- xs]

main :: IO ()
main = do
  input <- fmap (map parseNumber . lines) getContents
  print $ foldl1 (.+) input
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

