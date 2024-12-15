{- stack script
--resolver lts-14.20
--package container
-}
module Main where

import Data.Maybe
import Data.List
import qualified Data.Map as M
import qualified Data.Set as S
import qualified Data.Graph as G

splitOn :: Eq a => a -> [a] -> ([a], [a])
splitOn x xs = splitOn' [] x xs
  where
    splitOn' :: Eq a => [a] -> a -> [a] -> ([a], [a])
    splitOn' es _ []                 = (reverse es, [])
    splitOn' es y (x:xs) | x == y    = (reverse es, xs)
                         | otherwise = splitOn' (x:es) y xs

split :: Eq a => a -> [a] -> [[a]]
split _ [] = []
split x xs = takeWhile (/= x) xs : xs'
  where
    dropped = dropWhile (/= x) xs
    xs' = if null dropped then [] else split x $ tail dropped

apply :: (a -> b, c -> d) -> (a, c) -> (b, d)
apply (f, g) (x, y) = (f x, g y)


--------------------------------------------------------------------------------

data Graph = Graph {
  graph   :: G.Graph,
  getNode :: G.Vertex -> (Int, Int, [Int]),
  getVert :: Int -> Maybe G.Vertex
} 

createGraph :: [(Int, Int)] -> Graph
createGraph es = Graph g gn gv
  where
    (g, gn, gv) = G.graphFromEdges $ zipWith (\x y -> uncurry (x,,) y) [0..] $ parseEdges es
    
    adjList = M.fromList $ map (\x -> (x, [])) $ nub $ concatMap (\(x, y) -> [x, y]) es

    parseEdges :: [(Int, Int)] -> [(Int, [Int])]
    parseEdges es = M.toList $ foldr (\(x, y) m -> M.insertWith (\[x] xs -> x : xs) x [y] m) adjList es

fromList :: [(Int, Int, [Int])] -> Graph
fromList ns = Graph g gn gv where
  (g, gn, gv) = G.graphFromEdges ns

getSubGraph :: Graph -> [Int] -> Graph
getSubGraph g ps = fromList [f $ gn $ fromMaybe 0 x | x <- map gv ps, isJust x]
  where
    gn = getNode g
    gv = getVert g
    s = S.fromList ps

    f :: (Int, Int, [Int]) -> (Int, Int, [Int])
    f (id, v, es) = (id, v, filter (flip S.member s) es)

topSort :: Graph -> [Int] -> [Int]
topSort g p = map ((\(_, x, _) -> x) . gn') $ G.topSort sg'
  where
    sg@(Graph sg' gn' _) = getSubGraph g p

--------------------------------------------------------------------------------

getMiddle :: [a] -> a
getMiddle [x] = x
getMiddle (x:xs) = getMiddle $ init xs

task1 :: [(Int, Int)] -> [[Int]] -> Int
task1 rs ps = sum [getMiddle p | (p, p') <- zip ps $ map (topSort g) ps, p == p']
  where
    g = createGraph rs

task2 :: [(Int, Int)] -> [[Int]] -> Int
task2 rs ps = sum [getMiddle p' | (p, p') <- zip ps $ map (topSort g) ps, p /= p']
  where
    g = createGraph rs

--------------------------------------------------------------------------------

parseRules :: [String] -> [(Int, Int)]
parseRules ss = map parseRule ss
  where
    parseRule :: String -> (Int, Int)
    parseRule s = (read a, read b)
      where
        (a, b) = splitOn '|' s

parsePages :: [String] -> [[Int]]
parsePages ss = map (map read . split ',') ss

main :: IO ()
main = do
  (rules, pages) <- fmap (apply (parseRules, parsePages) . splitOn "" . lines) getContents
  putStr "Task 1: "
  print $ task1 rules pages
  putStr "Task 2: "
  print $ task2 rules pages


