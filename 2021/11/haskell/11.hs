{- stack script --resolver lts-14.20 
 --package split
 --package matrix-}
module Main where

import Data.List.Split (splitOn)
import Data.Matrix

type Pos = (Int, Int)

neighbors :: Int -> Int -> Pos -> [Pos]
neighbors rs cs (x, y) = filter inside [(x + a, y + b) | (a, b) <- dirs]
  where
    dirs          = filter (/= (0, 0)) $ (,) <$> [-1,0,1] <*> [-1,0,1]
    inside (x, y) = 0 < x && x <= rs && 0 < y && y <= cs

inc :: Matrix Int -> Pos -> Matrix Int
inc m p = setElem (m ! p + 1) p m

flash :: Matrix Int -> Pos -> Matrix Int
flash m p = m'
  where
    m' = foldl incAndFlash m ns
    ns = neighbors (nrows m) (ncols m) p

incAndFlash :: Matrix Int -> Pos -> Matrix Int
incAndFlash m p | m  ! p > 9 = m
                | m' ! p > 9 = flash m' p
                | otherwise  = m'
  where
    m' = inc m p

updateRound :: Matrix Int -> (Matrix Int, Int)
updateRound m = resetFlashes $ foldl incAndFlash m allPos
  where
    allPos         = [(x, y) | x <- [1..nrows m], y <- [1..ncols m]]
    resetFlashes :: Matrix Int -> (Matrix Int, Int)
    resetFlashes m = foldl (\(mat, cnt) pos -> if mat ! pos > 9 then (setElem 0 pos mat, cnt + 1) else (mat, cnt)) (m, 0) allPos


task1 :: Matrix Int -> Int
task1 m = task1' 0 0 m
  where
    task1' :: Int -> Int -> Matrix Int -> Int
    task1' 100  cnt _ = cnt
    task1' rs   cnt m = task1' (rs + 1) (cnt + cnt') m'
      where
        (m', cnt') = updateRound m

task2 :: Matrix Int -> Int
task2 m = task2' 1 m
  where
    task2' x mat | all (== 0) mat' = x
                 | otherwise       = task2' (x + 1) mat'
      where
        (mat', _) = updateRound mat

main :: IO ()
main = do
  input <- fmap (fromLists . map (map read . tail . splitOn "") . lines) getContents :: IO (Matrix Int)
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

