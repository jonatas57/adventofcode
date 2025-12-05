{- stack script --resolver lts-14.20 -package containers -}
module Main where

import qualified Data.Set as S

type Pos = (Int, Int)

adjPos :: Pos -> [Pos]
adjPos (x, y) = [(x', y') | x' <- [x - 1..x + 1], y' <- [y - 1..y + 1], x' /= x || y' /= y]

task1 :: [String] -> Int
task1 input = length $ filter (< 4) $ flip map pos $ (.) (length . filter id) $ flip (.) adjPos $ map $ flip S.member pset
  where
    pset = S.fromList pos
    pos  = map fst $ filter ((=='@') . snd) $ concat $ zipWith (\x s -> map (\(y, c) -> ((x, y), c)) $ zip [1..] s) [1..] input

task2 input = task2' pset
  where
    pset = S.fromList pos
    pos  = map fst $ filter ((=='@') . snd) $ concat $ zipWith (\x s -> map (\(y, c) -> ((x, y), c)) $ zip [1..] s) [1..] input

    task2' s | l == 0    = 0
             | otherwise = l + task2' s'
      where
        (s', l) = apply s

    apply :: S.Set Pos -> (S.Set Pos, Int)
    apply s = (s', length ps')
      where
        ps' = map fst $ filter ((< 4) . snd) $ map (\p -> (p, length [a | a <- map (flip S.member s) $ adjPos p, a])) $ S.toList s
        s'  = foldl (flip S.delete) s ps'

main :: IO ()
main = do
  input <- fmap lines getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

