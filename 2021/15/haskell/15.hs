{-
stack script --resolver lts-14.20
--package containers
--package pqueue
-}
{-# LANGUAGE GADTs #-}
module Main where

import Data.Char
import qualified Data.Map as M
import qualified Data.PQueue.Min as PQ

type Pos = (Int, Int)

matrix :: Int -> [Int] -> [[Int]]
matrix w [] = []
matrix w xs = (:) (take w xs) $ matrix w $ drop w xs

extend :: Int -> Int -> Int -> [Int] -> (Int, Int, [Int])
extend t n m xs = (t * n, t * m, mat)
  where
    mat  = concat $ zipWith sumAll [0..] $ replicate t mat'
    mat' = concat $ map (concat . zipWith sumAll [0..] . replicate t) $ matrix m xs
    sumAll :: Int -> [Int] -> [Int]
    sumAll x = zipWith (\a b -> mod (a + b - 1) 9 + 1) [x,x..]

enumerate :: Int -> Int -> [Int] -> M.Map Pos Int
enumerate n m xs = M.fromList $ flip zip xs $ (,) <$> [0..n - 1] <*> [0..m - 1]

getAdjacents :: Pos -> [Pos]
getAdjacents (x, y) = map (\(a, b) -> (x + a, y + b)) [(0, 1), (1, 0), (0, -1), (-1, 0)]

inf :: Int
inf = 1000000000

type Map   = M.Map Pos Int
type Queue = PQ.MinQueue (Int, Pos)

dijkstra :: Map -> Pos -> Pos -> Int
dijkstra g start end = dijkstra' (PQ.singleton (0, start)) (M.update (const $ Just 0) start $ fmap (const inf) g) end
  where
    dijkstra' :: Queue -> Map -> Pos -> Int
    dijkstra' q dist en | pos == en = dist M.! en
                        | otherwise = dijkstra' q' dist' en
      where
        (d, pos)    = PQ.findMin q
        adj         = filter (\p -> M.lookup p dist /= Nothing) $ getAdjacents pos
        adj'        = filter (\(x, p) -> x < dist M.! p) $ map (\p -> (d + g M.! p, p)) adj
        (q', dist') = foldl (.) id (map update adj') $ (PQ.deleteMin q, dist)
        update :: (Int, Pos) -> (Queue, Map) -> (Queue, Map)
        update (x, p) (q, m) = (PQ.insert (x, p) q, M.adjust (const x) p m)

task1 :: Int -> Int -> [Int] -> Int
task1 n m cave = dijkstra cave' (0, 0) (n - 1, m - 1)
  where
    cave' = enumerate n m cave

task2 :: Int -> Int -> [Int] -> Int
task2 n m cave = task1 n' m' cave'
  where
    (n', m', cave') = extend 5 n m cave

main :: IO ()
main = do
  input <- fmap lines getContents 
  let n    = length input
      m    = length $ head input
      cave = map (\c -> ord c - ord '0') $ concat input
  putStr "Task 1: "
  print $ task1 n m cave
  putStr "Task 2: "
  print $ task2 n m cave

