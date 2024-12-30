{- stack script --resolver lts-14.20 -}
module Main where

split :: Eq a => a -> [a] -> [[a]]
split _ [] = []
split x cs = split' [] x cs
  where
    split' :: Eq a => [a] -> a -> [a] -> [[a]]
    split' s _ [] = reverse s : []
    split' s x (c:cs) | x == c    = reverse s : split' [] x cs
                      | otherwise = split' (c:s) x cs

parse :: String -> (Int, [Int])
parse s = (val, xs)
  where
    [s1, s2] = split ':' s
    val      = read s1
    xs       = map read $ split ' ' $ dropWhile (== ' ') s2

solve :: [Int -> Int -> Int] -> Int -> [Int] -> Bool
solve _  val [x] | val == x  = True
                 | otherwise = False
solve fs val  xs             = any id $ map (solve fs val) xs'
  where
    xs'              = map (flip apply xs) fs

    apply :: (Int -> Int -> Int) -> [Int] -> [Int]
    apply f (x:y:xs) = f x y : xs

task fs es = sum $ map fst $ filter (uncurry $ solve fs) es

task1 = task [(*), (+)]

task2 = task [(*), (+), \x y -> read $ show x ++ show y]

main :: IO ()
main = do
  input <- map parse . lines <$> getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input
