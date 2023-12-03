{- stack script --resolver lts-14.20
                --package parsec -}
module Main where

import Text.Parsec hiding (parse)
import Data.Either

type Parser = Parsec String ()

parse :: Parsec String () a -> String -> Either ParseError a
parse p = runParser p () ""

number :: Parser Int
number = do
  int <- fmap read $ many1 digit
  return int

--------------------------------------------------------------------------------

data Game = Game Int [Draw] deriving Show
type Draw = (Color, Color, Color)
data Color = Red Int | Green Int | Blue Int deriving Show

colorToDraw :: Color -> Draw
colorToDraw (Red   r) = (Red r, Green 0, Blue 0)
colorToDraw (Green g) = (Red 0, Green g, Blue 0)
colorToDraw (Blue  b) = (Red 0, Green 0, Blue b)

emptyDraw :: Draw
emptyDraw = (Red 0, Green 0, Blue 0)

joinWith :: (Int -> Int -> Int ) -> Draw -> Draw -> Draw
joinWith f (Red r, Green g, Blue b) (Red r', Green g', Blue b') = (Red $ f r r', Green $ f g g', Blue $ f b b')

join :: Draw -> Draw -> Draw
join = joinWith (+)

--------------------------------------------------------------------------------

parseGame :: Parser Game
parseGame = do
  string "Game "
  id <- number
  string ": "
  draws <- sepBy parseDraw $ string "; "
  return $ Game id draws

parseColor :: Parser Color
parseColor = do
  cnt <- number
  many $ char ' '
  color <- string "red" <|> string "green" <|> string "blue"
  return $ case color of
    "red"   -> Red   cnt
    "green" -> Green cnt
    "blue"  -> Blue  cnt

parseDraw :: Parser Draw
parseDraw = do
  colors <- sepBy parseColor $ string ", "
  return $ foldl join emptyDraw $ map colorToDraw colors

--------------------------------------------------------------------------------

valid :: Draw -> Bool
valid (Red r, Green g, Blue b) = all id $ zipWith (<=) [r, g, b] [12, 13, 14]

draws :: Game -> [Draw]
draws (Game _ ds) = ds

gameId :: Game -> Int
gameId (Game id _) = id

getMax :: Game -> Game
getMax (Game id xs) = Game id $ (: []) $ foldl (joinWith max) emptyDraw xs

task1 :: [Game] -> Int
task1 gs = sum $ map gameId $ filter (valid . head . draws) $ map getMax gs

task2 :: [Game] -> Int
task2 gs = sum $ map (prod . head . draws . getMax) gs
  where
    prod :: Draw -> Int
    prod (Red r, Green g, Blue b) = r * g * b

main :: IO ()
main = do
  input <- fmap (rights . map (parse parseGame) . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

