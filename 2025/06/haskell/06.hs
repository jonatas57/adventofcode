{- stack script --resolver lts-14.20 -}
module Main where

split :: Eq a => a -> [a] -> [[a]]
split _ [] = [[]]
split c (x:xs) | x == c    = [] : xs'
               | otherwise = (x : hs) : ts
  where
    xs' = split c xs
    hs  = head xs'
    ts  = tail xs'

trim :: String -> String
trim = takeWhile (/= ' ') . dropWhile (== ' ')

transpose :: [[a]] -> [[a]]
transpose ([]:_) = []
transpose xs = map head xs : (transpose $ map tail xs)

task1 :: [String] -> [Int -> Int -> Int] -> Int
task1 ss fs = sum $ zipWith foldl1 fs $ transpose $ flip map ss $ map read . filter (not . null) . split ' '

task2 :: [String] -> [Int -> Int -> Int] -> Int
task2 ss fs = sum $ zipWith foldl1 fs $ map (map read) $ split [] $ map trim $ transpose ss

main :: IO ()
main = do
  input <- flip fmap getContents $ lines
  let ss = init input
      op = map (\x -> if x == "+" then (+) else (*)) $ filter (not . null) . split ' ' $ last input
  putStr "Task 1: "
  print $ task1 ss op
  putStr "Task 2: "
  print $ task2 ss op

