{- stack script --resolver lts-14.20 -}
module Main where

task1 input = sum $ map fst input'
  where
    s = map (\x -> if x == 'S' then '|' else x) $ head input
    input' = (0, s) : zipWith apply (map snd input') input

    apply xs ys = (length [(a, b) | (a, b) <- zip xs ys, a == '|', b == '^'], xs')
      where
        xs' = tail $ apply' ' ' xs ys

    apply' :: Char -> String -> String -> String
    apply' c []     _      = [c]
    apply' c (x:xs) (y:ys) | x == '|' && y == '^' = '|' : apply' '^' xs ('|' : tail ys)
                           | x == '|'             = c : apply' '|' xs ys
                           | otherwise            = c : apply' y xs ys

task2 input = sum $ foldl apply s $ tail input
  where
    s = map (\x -> if x == 'S' then 1 else 0) $ head input

    apply xs ys = tail $ apply' 0 0 xs ys

    apply' l r []     _      = [l]
    apply' l r (x:xs) (y:ys) | x > 0 && y == '^' = l + x : apply' r x xs ys
                             | otherwise         = l : apply' (x + r) 0 xs ys

main :: IO ()
main = do
  input <- flip fmap getContents lines
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

