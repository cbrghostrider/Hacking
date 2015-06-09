-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Array
import Data.List

nmax = 100
mmax = nmax
kmax = 100

data Direction = DOWN | RIGHT deriving (Show, Eq)
type PathVal = (Integer, Int)          -- (ways to get here, in these many turns) 
type CacheVal = ([PathVal], [PathVal]) -- various paths with these many number of turns, to end up at current cell, facing (DOWN, RIGHT)

mergeLists :: [PathVal] -> [PathVal] -> [PathVal]
mergeLists pvs [] = pvs
mergeLists [] pvs = pvs
mergeLists ((lw, lt) : lhs) ((rw, rt) : rhs) = 
  if lt == rt 
      then (lw + rw, lt) : mergeLists lhs rhs
      else if lt < rt
              then (lw, lt) : mergeLists lhs ((rw, rt) : rhs)
              else (rw, rt) : mergeLists ((lw, lt) : lhs) rhs

-- at each point, I look at top cell, and left cell
-- either i can keep moving in the same direction in top (down) or switch top (right) to top(down) by adding 1 more turn
-- either i can keep moving in the same direction in left (right) or switch left (down) to left (right) by adding 1 more turn
waysToGetHere :: CacheVal -> CacheVal -> CacheVal
waysToGetHere top@(topkdowns, topkrights) left@(leftkdowns, leftkrights) =
  let mykdowns  = mergeLists topkdowns   (map (\(n, t) -> (n, t+1)) topkrights)
      mykrights = mergeLists leftkrights (map (\(n, t) -> (n, t+1)) leftkdowns) 
  in  (mykdowns, mykrights)
  
computeCache :: Array (Int, Int) CacheVal
computeCache = cache 
  where
    -- how to get from (1, 1) to (r, c)
    sherlockMaze :: Int -> Int -> CacheVal
    sherlockMaze r c 
      | r == 1 && c == 1 = ([(1,0)], [(1,0)])
      | r == 1           = ([ ], [(1, 0)]) 
      | c == 1           = ([(1, 0)], [ ])
      | otherwise        = waysToGetHere (cache ! (r-1, c)) (cache ! (r, c-1))  

    cache = listArray ((0, 0), (nmax+1, mmax+1)) [ sherlockMaze ri ci | ri <- [0..(nmax+1)], ci <- [0..(mmax+1)] ]

main :: IO ()
main = do
  ip <- getContents
  let nmks = map (map read . words) . tail . lines $ ip
  let cachedVals = computeCache 
  mapM_ (putStrLn . show) $ 
           map (\[n, m, k] -> let (ds, rs) = (cachedVals ! (n, m)) 
                              in if n == 1 && m == 1
                                    then 1
                                    else ((`mod` (10^9 + 7)) . sum . map fst . filter ((<=k) . snd) $ ds ++ rs)) nmks


