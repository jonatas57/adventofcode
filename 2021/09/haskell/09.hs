{- stack script --resolver lts-14.20 
 --package split
 --package matrix -}
module Main where

import Data.List ( nub, sort )
import Data.List.Split
import Data.Matrix
import Data.Maybe

sumTuple :: (Int, Int) -> (Int, Int) -> (Int, Int)
sumTuple (x, y) (a, b) = (x + a, y + b)

getNeighbors :: Matrix Int -> (Int, Int) -> [Int]
getNeighbors m pos = map (fromMaybe 0) $ filter (/= Nothing) $ map (\(x, y) -> safeGet x y m) $ map (sumTuple pos) dirs
  where
    dirs = [(-1, 0), (0, 1), (1, 0), (0, -1)]

task1 :: Matrix Int -> Int
task1 m = sum $ map (\x -> 1 + m ! x) lowps
  where
    ids   = [(x, y) | x <- [1..nrows m], y <- [1..ncols m]]
    lowps = map fst $ filter (\(x, y) -> m ! x < foldl1 min y) $ zip ids $ map (getNeighbors m) ids

data UnionFind = UnionFind (Matrix Int) (Matrix (Int, Int)) deriving Show

unionFind :: Matrix Int -> UnionFind
unionFind m = UnionFind (createMat [1,1..] :: Matrix Int) $ createMat [(x, y) | x <- [1..rs], y <- [1..cs]]
  where
    createMat = fromList rs cs
    rs        = nrows m
    cs        = ncols m

find :: UnionFind -> (Int, Int) -> (UnionFind, (Int, Int))
find uf@(UnionFind sz id) pos | id ! pos == pos = (uf, pos)
                              | otherwise       = ((UnionFind sz $ setElem par pos id), par)
  where 
    (uf', par) = find uf $ id ! pos

join :: UnionFind -> (Int, Int) -> (Int, Int) -> UnionFind
join uf@(UnionFind sz id) a b | a' == b'  = uf
                              | otherwise = UnionFind (setElem (sz ! a'' + sz ! b'') b'' sz) (setElem b'' a'' id)
  where
    (uf', a')  = find uf  a
    (uf'', b') = find uf' b
    (a'', b'') = if sz ! a' > sz ! b' then (b', a') else (a', b')

task2 :: Matrix Int -> Int
task2 m = product $ take 3 $ reverse $ sort basins
  where
    uf                     = unionFind m
    rs                     = nrows m
    cs                     = ncols m
    basins                 = map (sz !) $ nub $ map (snd . find uf') $ allPos
    allPos                 = filter (\x -> m ! x < 9) $ (,) <$> [1..rs] <*> [1..cs]
    neighbors (x, y)       = [(x - 1, y), (x, y - 1)]
    uf'@(UnionFind sz id)  = joinAll uf $ concatMap (\x -> zip (repeat x) $ filter (\x -> inside x && m ! x < 9) $ neighbors x) allPos
    inside (x, y)          = 0 < x && x <= rs && 0 < y && y <= cs
    joinAll uf []          = uf
    joinAll uf ((p, q):ps) = joinAll (join uf p q) ps

main :: IO ()
main = do
  input <- (fmap (fromLists . map (map read . tail . splitOn "") . lines) getContents :: IO (Matrix Int))
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

