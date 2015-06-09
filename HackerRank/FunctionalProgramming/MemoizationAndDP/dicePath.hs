-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Array
import Data.List

mmax = 60
nmax = mmax

data Rotation = DOWN | RIGHT deriving (Show, Eq)

-- die values for (top, under, left, right, front, back) faces
type Die      = (Int, Int, Int, Int, Int, Int)

startDie :: Die
startDie = (1, 6, 3, 4, 2, 5) --verified!

dieValue :: Die -> Int
dieValue (v, _, _, _, _, _) = v

rotateDie :: Die -> Rotation -> Die
rotateDie (pt, pu, pl, pr, pf, pb) DOWN  = (pb, pf, pl, pr, pt, pu)
rotateDie (pt, pu, pl, pr, pf, pb) RIGHT = (pl, pr, pu, pt, pf, pb)

-- takes (pathsum, dies) from previous cell, and computes best (pathsum, dies) to this cell
--
-- Very tricky case here! 
-- We can't just keep the best path, because of two reasons:
-- 1. First, we can reach the same best path value but end up with different die orientations
--         Later on in the recursion this is significant, because depending on the orientation, 
--         a DOWN or RIGHT could make different values pop up. so we have to save all the dies
--         that result in max path value at that cell.
-- 2. But wait. We also have to save (pathsum, dies) that don't result in the max path value 
--         at that cell. Why the hell? Because say you have 2 paths to (m, n-1) that end in 
--         values (15, die face 2 top) and (14, die face 1 top). However, when you rotate RIGHT
--         to reach (m, n) in the next step, the rotation on the first die might give you 3
--         and the rotation on the next die might give you 6! So now the maxpath is actually 20
--         and not 18 as you would have computed had you only saved the 15.
--      So how many such paths should we save? Keep in mind that the *number* of rotations needed
--      to arrive at any cell from (1, 1) is the same (though their top face values may be different)
--      Since 6 is the Max value of the die, this means that once the pathsums differ by more than 6 
--      compared to the maxpath so far, we can drop those candidates (since to catch up, we would 
--      require more *number* of rotations). This is why the code below considers the magic number 6 
--      in the comparison!
computeBestCandidates :: Rotation -> [(Int, Die)] -> [(Int, Die)]
computeBestCandidates rot []   = []
computeBestCandidates rot psds = 
  let newdies = map (\die -> rotateDie die rot) $ map snd psds
      dievals = map dieValue newdies
      newsums = map (\(x, y) -> x + y) $ zip dievals $ map fst psds
      maxval  = maximum newsums
      bestsumdies = filter (\(s, _) -> (maxval - s) <= 6) $ zip newsums newdies -- see note above for why 6
  in  nub bestsumdies

computeCache :: Int -> Int -> Array (Int, Int) [(Int, Die)]
computeCache m n = cache
  where
    -- max path sum to get from (1, 1) to (r, c) , 
    -- when die is currently at (m, n) in state "die"
    maxPathSum :: Int -> Int -> Int -> Int -> [(Int, Die)]
    maxPathSum m n r c = go r c 
    go ri ci
        | ri <= 1 && ci <= 1 = [(dieValue startDie, startDie)]
        | ri <= 1            = computeBestCandidates RIGHT (cache ! (ri, ci-1)) 
        | ci <= 1            = computeBestCandidates DOWN  (cache ! (ri-1, ci))
        | otherwise          = let topsds  = cache ! (ri-1, ci)
                                   leftsds = cache ! (ri, ci-1)
                                   fromtopsds  = computeBestCandidates DOWN topsds
                                   fromleftsds = computeBestCandidates RIGHT leftsds
                                   maxval  = maximum $ (map fst fromtopsds) ++ (map fst fromleftsds)
                                   bestsds = filter (\(s, _) -> (maxval-s) <= 6) $ fromtopsds ++ fromleftsds
                               in  nub bestsds
    cache  = listArray ((0, 0), (m+1, n+1)) [ maxPathSum m n rv cv | rv <- [0..(m+1)], cv <- [0..(n+1)]]

main :: IO ()
main = do
  ip <- getContents
  let mnstrs = tail . lines $ ip
  let mns    = map (map read . words) $ mnstrs
  let cacheVals = computeCache mmax nmax
  mapM_ (putStrLn . show) $ map (\[m, n] -> (maximum . map fst $ (cacheVals ! (m, n))) ) mns
  
