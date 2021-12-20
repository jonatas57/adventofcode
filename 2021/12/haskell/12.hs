{- stack script --resolver lts-14.20 
 --package containers
 --package split
-}
module Main where

import           Data.Char
import           Data.List
import           Data.List.Split ( splitOn )
import qualified Data.Map        as M

data Cave = Start | End | Small String | Large String deriving (Eq, Ord, Show)

strToCave :: String -> Cave
strToCave "start"   = Start
strToCave "end"     = End
strToCave ~s@(c:cs) | isUpper c = Large s
                    | otherwise = Small s

type Path  = [Cave]
type Graph = M.Map Cave [Cave]

createGraph :: [[String]] -> Graph
createGraph es = M.fromList $ zip vs adj
  where
    vs  = map strToCave $ nub $ concat es
    adj = map (\c -> concatMap (map strToCave . tail) $ filter (\[x, y] -> c == strToCave x && Start /= strToCave y) es') vs
    es' = es ++ map reverse es

visit :: Maybe Bool -> Maybe Bool
visit Nothing = Nothing
visit _       = Just True

getPaths :: Bool -> Graph -> Cave -> M.Map Cave Bool -> Int
getPaths _       _    End      _                 = 1
getPaths revisit g c@(Start)   m                 = sum $ map (\x -> getPaths revisit g x $ M.alter visit c m) $ g M.! c
getPaths revisit g c@(Large _) m                 = sum $ map (\x -> getPaths revisit g x m) $ g M.! c
getPaths revisit g c@(Small _) m | not $ m M.! c = sum $ map (\x -> getPaths revisit g x $ M.alter visit c m) $ g M.! c
                                 | revisit       = sum $ map (\x -> getPaths False   g x m) $ g M.! c
                                 | otherwise     = 0
 
task1 :: Graph -> Int
task1 g = getPaths False g Start $ M.fromList $ zip (M.keys g) $ repeat False

task2 :: Graph -> Int
task2 g = getPaths True g Start $ M.fromList $ zip (M.keys g) $ repeat False

main :: IO ()
main = do
  input <- fmap (createGraph . map (splitOn "-") . lines) getContents
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

