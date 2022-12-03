{- stack script --resolver lts-14.20 -}
module Main where

import Data.Char

data JKP = Rock | Paper | Scissors deriving (Eq, Enum)
data Outcome = Lose | Draw | Win deriving Enum

outcome :: JKP -> JKP -> Outcome
outcome Rock     Paper    = Win
outcome Paper    Scissors = Win
outcome Scissors Rock     = Win
outcome a b | a == b      = Draw
            | otherwise   = Lose

score :: JKP -> JKP -> Int
score a b = (fromEnum b + 1 +) $ (3 *) $ fromEnum $ outcome a b

task1 :: [(Int, Int)] -> Int
task1 = sum . map (uncurry score . getRound)
  where
    getRound :: (Int, Int) -> (JKP, JKP)
    getRound (a, b) = (toEnum a, toEnum b)

fromOutcome :: JKP -> Outcome -> JKP
fromOutcome a Win  = toEnum $ (fromEnum a + 1) `mod` 3
fromOutcome a Draw = a
fromOutcome a Lose = toEnum $ (fromEnum a + 2) `mod` 3

task2 :: [(Int, Int)] -> Int
task2 = task1 . map parse
  where
    parse (a, b) = (a, fromEnum $ fromOutcome a' b')
      where
        a' = toEnum a
        b' = toEnum b

main :: IO ()
main = do
  input <- fmap (map (\[a, b] -> (ord (head a) - ord 'A', ord (head b) - ord 'X')) . map words . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input
