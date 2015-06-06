-- Unfortunately my solution currently has some bug
-- Only 5/10 test cases pass right now
--
-- Note: Special thanks to kseo for Union-Find implementation, which I re-used
--
import Control.Monad
import Data.List
import Debug.Trace
import Data.Array.Unboxed

------------------------------------------------------------------------------------------
--      This Union-Find implementation is credited to:
--      https://gist.github.com/kseo/8693028 
------------------------------------------------------------------------------------------

import Control.Monad
import Control.Monad.ST
import Data.Array.MArray
import Data.Array.ST
import Data.STRef
 
import Prelude hiding (id)
 
data UnionFind s = UnionFind {
    ids:: STUArray s Int Int
  , szs:: STUArray s Int Int
  }
 
newUnionFind :: Int -> ST s (UnionFind s)
newUnionFind n = liftM2 UnionFind (newListArray (0, n-1) [0..n-1]) (newArray (0, n-1) 1)
 
find :: (UnionFind s) -> Int -> Int -> ST s Bool
find uf p q = liftM2 (==) (root uf p) (root uf q)
 
root :: (UnionFind s) -> Int -> ST s Int
root uf i = do
    id <- readArray (ids uf) i
    if (id /= i)
        then do
            gpid <- readArray (ids uf) id
            writeArray (ids uf) i gpid
            root uf id
        else return i
 
unite :: (UnionFind s) -> Int -> Int -> ST s ()
unite uf p q = do
    i <- root uf p
    j <- root uf q
    szi <- readArray (szs uf) i
    szj <- readArray (szs uf) j
    if (szi < szj)
        then do
            writeArray (ids uf) i j
            writeArray (szs uf) j (szi + szj)
        else do
            writeArray (ids uf) j i
            writeArray (szs uf) i (szj + szi)

------------------------------------------------------------------------------------------
--      end credit
------------------------------------------------------------------------------------------

ufSizes :: (UnionFind s) -> Int -> ST s [Int]
ufSizes uf (-1) = return []
ufSizes uf n = do
  os <- ufSizes uf (n-1) 
  id <- readArray (ids uf) n
  if (id == n)
    then do
      szn <- readArray (szs uf) n
      return (szn:os)
    else do
      return os

cacheTruckSizes :: [Int]
cacheTruckSizes =  1 : [ (ceiling . sqrt $ n) | n <- [1..]]

-- takes number of inmates, handcuffed pairs, and return a list of lengths of groups
groupInmatesUF :: Int -> [[Int]] -> [Int]
groupInmatesUF ninmates pss = runST $ do 
  uf <- newUnionFind ninmates
  forM pss $ \ps -> do
    unite uf (head ps - 1) (last ps - 1)
  os <- ufSizes uf (ninmates-1)
  return os

prisonTransport :: [Int] -> Int
prisonTransport groups =  (sum . map (cacheTruckSizes !!) $ groups )

main :: IO ()
main = do
  ninmates <- getLine
  npairs   <- getLine
  pairs    <- forM [1..(read npairs)] $ \_ -> getLine
  let imarr = groupInmatesUF (read ninmates) (map (map read . words) pairs)
  let cost  = prisonTransport imarr
  putStrLn (show cost)
