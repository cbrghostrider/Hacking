-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Array

type Coin = Int

-- Previous solution using list monad (slow due to overlapping subproblem recomputation)
applyAmt :: Coin -> (Int, [(Int, Int)]) -> [(Int, [(Int, Int)])]
applyAmt d (amt, cs) = map (\nc -> (amt - d*nc, (nc, d): cs)) $ [0..(amt `div` d)]

computeWays' :: [Coin] -> Int ->Int 
computeWays' cs tgtAmt = length . filter (\(r, _) -> r == 0) . foldl' (>>=) (return (tgtAmt, [])) . map applyAmt $ cs

-- Solution using dynamic programming (fast!)
computeWays :: [Coin] -> Int -> Int
computeWays cs n = go (length cs) n
  where
    go ci vi
      |  vi == 0   = 1 -- how many ways to make zero value? One way only... to take no coins.
      |  ci == 0   = 0 -- how many ways to make non-zero value from no coins?
      |  otherwise = sum . map (\v -> cache ! ((ci-1), v)) . map (vi -) . takeWhile (<= vi) . map (* (cs !! (ci-1))) $ [0..]
    cache = listArray ((0, 0), (length cs, n)) [ go cind vind | cind <- [0..(length cs)], vind <- [0..n] ]

-- main driver program
main :: IO ()
main = do
  nmstr <- getLine
  cstr  <- getLine
  let [n, m] = map read . words $ nmstr
  let cs     = map read . words $ cstr
  putStrLn . show $ computeWays cs n
