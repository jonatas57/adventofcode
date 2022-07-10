{- stack script --resolver lts-14.20 -}
{-# LANGUAGE GADTs #-}
{-# LANGUAGE StandaloneDeriving #-}
module Main where

import Data.Bits
import Data.Char

int2list :: Int -> [Int]
int2list x = map ((1 .&.) . shift x) [-3, -2, -1, 0]

hexDigit :: Char -> Int
hexDigit c | isDigit c = ord c - ord '0'
           | otherwise = ord c - ord 'A' + 10

hex2bin :: String -> [Int]
hex2bin xs = concatMap (int2list . hexDigit) xs

lift :: Int -> Int -> Int
lift x b = shift x 1 + b

evalBin :: [Int] -> Int
evalBin = foldl lift 0

mapTuple :: (a -> b, c -> d) -> (a, c) -> (b, d)
mapTuple (f, g) (x, y) = (f x, g y)

--------------------------------------------------------------------------------

data Packet where
  Sum   :: Int -> [Packet] -> Packet 
  Prod  :: Int -> [Packet] -> Packet 
  Min   :: Int -> [Packet] -> Packet 
  Max   :: Int -> [Packet] -> Packet 
  Lit   :: Int -> Int -> Packet
  Grt   :: Int -> [Packet] -> Packet 
  Less  :: Int -> [Packet] -> Packet 
  Equal :: Int -> [Packet] -> Packet 
deriving instance Show Packet

packetsBuilders :: [Int -> [Packet] -> Packet]
packetsBuilders = [Sum, Prod, Min, Max, undefined, Grt, Less, Equal]

getVersion :: Packet -> Int
getVersion (Sum   v _) = v
getVersion (Prod  v _) = v
getVersion (Min   v _) = v
getVersion (Max   v _) = v
getVersion (Lit   v _) = v
getVersion (Grt   v _) = v
getVersion (Less  v _) = v
getVersion (Equal v _) = v

getSubPackets :: Packet -> [Packet]
getSubPackets (Sum   _ ps) = ps
getSubPackets (Prod  _ ps) = ps
getSubPackets (Min   _ ps) = ps
getSubPackets (Max   _ ps) = ps
getSubPackets (Lit   _  _) = []
getSubPackets (Grt   _ ps) = ps
getSubPackets (Less  _ ps) = ps
getSubPackets (Equal _ ps) = ps

parseNPackets :: Int -> [Int] -> ([Packet], [Int])
parseNPackets 0 xs = ([], xs)
parseNPackets n xs = (p : ps, xs'')
  where
    (p , xs' ) = parsePacket' xs
    (ps, xs'') = parseNPackets (n - 1) xs'

parseAllPackets :: [Int] -> ([Packet], [Int])
parseAllPackets [] = ([], [])
parseAllPackets xs = (p : ps, xs'')
  where
    (p , xs' ) = parsePacket' xs
    (ps, xs'') = parseAllPackets xs'

parseSubPackets :: [Int] -> ([Packet], [Int])
parseSubPackets ~(x:xs) | x == 0    = mapTuple (id, (++ xs')) $ parseAllPackets allp
                        | otherwise = parseNPackets mode1 xs1
  where
    (mode0, xs0) = mapTuple (evalBin, id) $ splitAt 15 xs
    (allp, xs')  = splitAt mode0 xs0
    (mode1, xs1) = mapTuple (evalBin, id) $ splitAt 11 xs

parseLiteral :: [Int] -> (Int, [Int])
parseLiteral xs = parseLiteral' 0 xs
  where
    parseLiteral' x xs | t == 1    = parseLiteral' (shift val 4) xs'
                       | otherwise = (val, xs')
      where
        (bs, xs') = splitAt 5 xs
        (t:num)   = bs
        val       = x + evalBin num

parsePacket' :: [Int] -> (Packet, [Int])
parsePacket' xs | tid == 4  = (Lit vs lit, xs3)
                | otherwise = (flip uncurry (vs, sub) $ packetsBuilders !! tid, xs2)
  where
    (vs , xs0) = mapTuple (evalBin, id) $ splitAt 3 xs
    (tid, xs1) = mapTuple (evalBin, id) $ splitAt 3 xs0
    (sub, xs2) = parseSubPackets xs1
    (lit, xs3) = parseLiteral xs1

parsePacket :: [Int] -> Packet
parsePacket = fst . parsePacket'

eval :: Packet -> Int
eval (Sum   _ ps) = sum     $ map eval ps
eval (Prod  _ ps) = product $ map eval ps
eval (Min   _ ps) = minimum $ map eval ps
eval (Max   _ ps) = maximum $ map eval ps
eval (Lit   _  v) = v
eval (Grt   _ ps) = if eval (head ps) >  eval (last ps) then 1 else 0
eval (Less  _ ps) = if eval (head ps) <  eval (last ps) then 1 else 0
eval (Equal _ ps) = if eval (head ps) == eval (last ps) then 1 else 0

--------------------------------------------------------------------------------
task1 :: Packet -> Int
task1 p = (getVersion p +) . sum . map task1 $ getSubPackets p

task2 :: Packet -> Int
task2 = eval

--------------------------------------------------------------------------------
main :: IO ()
main = do
  input <- flip fmap getContents $ parsePacket . hex2bin
  putStr "Task 1: "
  print $ task1 input
  putStr "Task 2: "
  print $ task2 input

