{- stack script --resolver lts-14.20 -}
module Main where

import Text.Parsec hiding (parse)
import Text.Parsec.Char

parse :: Parsec String () a -> String -> Either ParseError a
parse p s = runParser p () "" s

parseMul :: Parsec String u Int
parseMul = do
  string "mul("
  a <- fmap read $ many1 digit
  char ','
  b <- fmap read $ many1 digit
  char ')'
  return $ a * b

--------------------------------------------------------------------------------

splitBefore :: Char -> String -> [String]
splitBefore _ [] = []
splitBefore c  s = prefix s : (splitBefore c $ suffix s)
  where
    prefix []      = []
    prefix (c':cs) = c' : takeWhile (/= c) cs

    suffix [] = []
    suffix (_:cs) = dropWhile (/= c) cs

--------------------------------------------------------------------------------

fromParse :: Either ParseError Int -> Int
fromParse (Left  _) = 0
fromParse (Right x) = x

task1 :: String -> Int
task1 input = sum $ map (fromParse . parse parseMul) $ splitBefore 'm' input

--------------------------------------------------------------------------------

data ABC = A Int | B Bool | C () deriving Show

parseDo :: Parsec String u Bool
parseDo = do
  string "do()"
  return True

parseDont :: Parsec String u Bool
parseDont = do
  string "don't()"
  return False

parseAny :: Parsec String u ABC
parseAny = do
  mul <- optionMaybe $ try parseMul
  case mul of
    Just a  -> return $ A a
    Nothing -> do
      on <- optionMaybe $ try parseDo
      case on of
        Just _ -> return $ B True
        Nothing -> do
          off <- optionMaybe $ try parseDont
          case off of
            Just _  -> return $ B False
            Nothing -> return $ C ()

fromABC :: ABC -> Either Bool Int
fromABC (A a) = Right a
fromABC (B b) = Left b
fromABC (C _) = Right 0

fromParse2 :: Either ParseError ABC -> Either Bool Int
fromParse2 (Left  _) = Right 0
fromParse2 (Right a) = fromABC a

solve :: Int -> Bool -> [Either Bool Int] -> Int
solve acc _     []             = acc
solve acc _     ((Left  b):es) = solve acc b es
solve acc False (       _ :es) = solve acc False es
solve acc True  ((Right x):es) = x + solve acc True es

task2 input = solve 0 True $ map (fromParse2 . parse parseAny) $ concatMap (splitBefore 'd') $ splitBefore 'm' input

main :: IO ()
main = do
  input <- flip fmap getContents $ concat . lines
  print $ map (fromParse . parse parseMul) $ splitBefore 'm' input
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input


