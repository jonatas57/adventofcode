{- stack script --resolver lts-14.20 -}

task1 :: [Int] -> Int
task1 xs = length $ filter (== 0) $ task1' 50 xs
  where
    task1' :: Int -> [Int] -> [Int]
    task1' _    []  = []
    task1' x (y:ys) = z : task1' z ys
      where
        z = flip mod 100 $ (+100) $ flip mod 100 $ x + y

task2 :: [Int] -> Int
task2 xs = sum $ task2' 50 xs
  where
    task2' :: Int -> [Int] -> [Int]
    task2' _    []  = []
    task2' x (y:ys) = cnt : task2' z ys
      where
        z   = flip mod 100 $ (+100) $ flip mod 100 $ x + y
        sum | y >= 0    = x + y
            | otherwise = (flip mod 100 $ 100 - x) - y
        cnt = div sum 100

main :: IO ()
main = do
  input <- fmap (map (read . (\(c:cs) -> (if c == 'L' then '-' else ' ') : cs)) . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input
