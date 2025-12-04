{- stack script --resolver lts-14.20 --package containers -}
module Main where

import qualified Data.Set as S
import Data.Maybe

split :: Eq a => a -> [a] -> [[a]]
split _ [] = [[]]
split c (x:xs) | x == c    = [] : xs'
               | otherwise = (x : hs) : ts
  where
    xs' = split c xs
    hs  = head xs'
    ts  = tail xs'

getUpperBound :: String -> Int
getUpperBound s | h < len - h = read $ '1' : replicate h '0'
                | l < r       = l + 1
                | otherwise   = l
  where
    len = length s
    h   = len `div` 2
    l'  = take h s
    r'  = drop h s
    l   = read l'
    r   = read r'

getLowerBound :: String -> Int
getLowerBound s | h < len - h = read $ replicate h '9'
                | l > r       = l - 1
                | otherwise   = l
  where
    len = length s
    h   = len `div` 2
    l'  = take h s
    r'  = drop h s
    l   = read l'
    r   = read r'

getInterval s = (l', r')
  where
    [l, r] = split '-' s
    l'     = getUpperBound l
    r'     = getLowerBound r

task1 :: [String] -> Int
task1 input = sum $ map read $ concat [map (\x -> show x ++ show x) [l..r] | (l, r) <- [p | p@(x, y) <- map getInterval input, x <= y]]

createReplicates :: Int -> [String]
createReplicates x = createReplicates' x' (x' ++ x')
  where
    x' = show x
    createReplicates' x s = s : createReplicates' x (x ++ s)

task2 :: [String] -> Int
task2 input = foldl (+) 0 $ S.fromList $ map fst $ filter (uncurry (==) . snd) $ concat $ takeWhile (not . null) $ map getPossibleIntervals [1..]
  where
    is = flip map input $ map read . split '-'
    l  = S.fromList $ map head is
    r  = S.fromList $ map last is

    getPossibleIntervals :: Int -> [(Int, (Maybe Int, Maybe Int))]
    getPossibleIntervals x = intervals
      where
        rep        = map read . take 10 $ createReplicates x
        intervals  = zip rep $ takeWhile (isJust . snd) $ map interval rep
        interval v = (S.lookupLE v l >>= flip S.lookupIndex l, S.lookupGE v r >>= flip S.lookupIndex r)

main :: IO ()
main = do
  input <- flip fmap getContents $ split ',' . head . lines
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input
