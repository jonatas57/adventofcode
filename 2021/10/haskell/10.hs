{- stack script --resolver lts-14.20 -}

module Main where

import Data.List (sort)

data Stack = EmptyStack | Stack String | ErrorStack Int deriving Show

closePair :: Char -> Char
closePair '(' = ')'
closePair '[' = ']'
closePair '{' = '}'
closePair '<' = '>'
closePair _   = ' '

isOpen :: Char -> Bool
isOpen = flip elem "([{<"

pop :: Stack -> Stack
pop (Stack [x])    = EmptyStack
pop (Stack (x:xs)) = Stack xs
pop st             = st

getStack :: String -> Stack
getStack s = getStack' s EmptyStack
  where
    getStack' []      st                                 = st
    getStack' _       es@(ErrorStack _)                  = es
    getStack' (c:cs) s@(Stack (d:ds)) | c == closePair d = getStack' cs $ pop s
                                      | isOpen c         = getStack' cs (Stack (c:d:ds))
                                      | otherwise        = ErrorStack $ getVal c
    getStack' (c:cs) EmptyStack       | isOpen c         = getStack' cs (Stack (c:[]))
                                      | otherwise        = ErrorStack $ getVal c
    getVal ')' = 3
    getVal ']' = 57
    getVal '}' = 1197
    getVal '>' = 25137

isError :: Stack -> Bool
isError (ErrorStack _) = True
isError _              = False

task1 :: [Stack] -> Int
task1 ss = foldl (\s (ErrorStack x) -> s + x) 0 $ filter isError ss

task2 :: [Stack] -> Int
task2 ss = middle $ sort $ map (\(Stack ss) -> evalStack 0 ss) $ filter (not . isError) ss
  where
    middle :: [Int] -> Int
    middle []    = 0
    middle [x]   = x
    middle [x,y] = x
    middle xs    = middle $ init $ tail $ xs
    evalStack :: Int -> String -> Int
    evalStack x []     = x
    evalStack x (c:cs) = evalStack ((5 * x +) $ getVal $ closePair c) cs
    getVal :: Char -> Int
    getVal ')' = 1
    getVal ']' = 2
    getVal '}' = 3
    getVal '>' = 4

main :: IO ()
main = do
  input <- fmap (map getStack . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

