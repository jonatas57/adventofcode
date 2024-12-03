{- stack script --resolver lts-14.20 -}
module Main where

check :: [Int] -> Bool
check xs = valid $ check' 0 xs
  where
    valid :: [Int] -> Bool
    valid = all (\x -> 1 <= x && x <= 3)

    check' :: Int -> [Int] -> [Int]
    check' _ [_] = [1]
    check' dir (x:y:xs) | dir' /= 0 && dir' * dir /= -1 = del : check' dir' (y:xs)
                        | otherwise                    = [0]
      where
        dir' | x < y     = -1
             | x > y     = 1
             | otherwise = 0
        del = abs $ x - y

bool2int :: Bool -> Int
bool2int True  = 1
bool2int False = 0

task1 :: [[Int]] -> Int
task1 xs = sum $ flip map xs $ bool2int . check

--------------------------------------------------------------------------------------------------

data Zipper a = Zip {
  left  :: [a]
, focus :: a
, right :: [a]
}

zipper :: [a] -> Zipper a
zipper (x:xs) = Zip [] x xs

next :: Zipper a -> Zipper a
next (Zip ls f (r:rs)) = Zip (f:ls) r rs
next z                 = z

dampener :: [Int] -> [[Int]]
dampener xs = dampener' $ zipper xs
  where
    dampener'   (Zip ls _ []) = [reverse ls]
    dampener' z@(Zip ls f rs) = (flip (++) rs $ reverse ls) : (dampener' $ next z)

task2 xs = sum $ flip map xs $ bool2int . (\x -> if check x then True else any check $ dampener x)

main :: IO ()
main = do
  input <- fmap (fmap (fmap read . words) . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input


