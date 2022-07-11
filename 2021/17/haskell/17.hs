{- stack script --resolver lts-14.20 -}
module Main where

import Data.Char hiding (isNumber)

type Interval = (Int, Int)
type Pos      = (Int, Int)
type Area     = (Interval, Interval)

splitWhile :: (a -> Bool) -> [a] -> ([a], [a])
splitWhile f ls = splitWhile' f ([], ls)
  where
    splitWhile' f xs@(_, [])                 = xs
    splitWhile' f    (l, (r:rs)) | f r       = splitWhile' f (l ++ [r], rs)
                                 | otherwise = (l, (r:rs))

isNumber :: Char -> Bool
isNumber v = isDigit v || v == '-'

parseInput :: String -> Area
parseInput xs = ((read x0, read x1), (read y0, read y1))
  where
    ( _, xs0) = splitWhile (not . isNumber) xs
    (x0, xs1) = splitWhile        isNumber  xs0
    ( _, xs2) = splitWhile (not . isNumber) xs1
    (x1, xs3) = splitWhile        isNumber  xs2
    ( _, xs4) = splitWhile (not . isNumber) xs3
    (y0, xs5) = splitWhile        isNumber  xs4
    ( _, xs6) = splitWhile (not . isNumber) xs5
    (y1,   _) = splitWhile        isNumber  xs6

insideInterval :: Interval -> Int -> Bool
insideInterval (l, r) x = l <= x && x <= r

insideArea :: Area -> Pos -> Bool
insideArea (xs, ys) (x, y) = insideInterval xs x && insideInterval ys y

task1 :: Area -> Int
task1 (_, (yl, yr)) = flip div 2 $ (*) y $ y + 1
  where
    y = if yl < 0 then -yl - 1 else yr

nextVel :: Pos -> Pos
nextVel (x, y) = (goTo0 x, y - 1)

goTo0 :: Int -> Int
goTo0 x | x == 0    = 0
        | otherwise = x - div x (abs x)

beforeArea :: Area -> Pos -> Bool
beforeArea ((_, xr), (yl, _)) (x, y) = x <= xr && y >= yl

check :: Area -> Pos -> Bool
check a v = insideArea a $ last ok
  where
    ok = takeWhile (beforeArea a) $ gen v
    gen :: Pos -> [Pos]
    gen v0@(vx, vy) = (:) (0, 0) $ map (\(px, py) -> (px + vx, py + vy)) $ gen $ nextVel v0

canReach :: Bool -> Interval -> (Int -> Int) -> Int -> Int -> Bool
canReach isX rng nxt x0 v | isX && v == 0 = insideInterval rng x0
                          | x0 > snd rng  = False
                          | otherwise     = insideInterval rng x0 || (canReach isX rng nxt (x0 + v) $ nxt v)

task2 :: Area -> Int
task2 a@((xl, xr), (yl, yr)) = length ok
  where
    vs = (,) <$> possibleXs [0..xr] <*> possibleYs [yl..abs yl]
    ok = filter (check a) vs
    possibleXs :: [Int] -> [Int]
    possibleXs xs = filter (canReach True (xl, xr) goTo0 0) xs
    possibleYs :: [Int] -> [Int]
    possibleYs ys = map negate $ filter (canReach False (-yr, -yl) ((+) 1) 0) ys

main :: IO ()
main = do
  input <- fmap parseInput getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

