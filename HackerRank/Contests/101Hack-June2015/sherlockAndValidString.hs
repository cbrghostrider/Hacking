-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import qualified Data.Map as M
import Data.List

validSeq [] = True
validSeq ls = all (== head ls) ls

solveProblem :: String -> String 
solveProblem [] = "YES"
solveProblem ss = 
  let minit = M.empty
      mfinal= foldl' (\macc c -> let res = M.lookup c macc 
                                 in  if res == Nothing 
                                        then M.insert c 1 macc 
                                        else let (Just v) = res in M.insert c (v+1) macc) minit $ ss
      ls    = sort $ M.elems mfinal
      lss   = map (\(p, seql) -> (take p seql) ++ [(seql !! p) - 1] ++ (drop (p+1) seql)) . take (length ls) . zip [0..] $ repeat ls
      somevalid = any (== True) . map (validSeq . sort . filter (>0)) $ lss
  in  (if validSeq ls || somevalid then "YES" else "NO")

main :: IO ()
main = do
  ip <- getLine
  let istr = head . lines $ ip
  putStrLn $ solveProblem istr
