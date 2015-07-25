-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

foldSticks :: (Int, [Int]) -> Int -> (Int, [Int])
foldSticks (curCut, clens) stick = 
  let seq1  = (1 + head clens) : (tail clens)
      seq2  = 1:clens
  in  if curCut == stick then (curCut, seq1) else (stick, seq2)

stickCuts :: [Int] -> [Int]
stickCuts ss = cutSeqs
  where numCuts = reverse . snd . foldl' foldSticks (0, []) $ sort ss
        cutSeqs = init . scanl (\acc c -> acc - c) numsticks $ numCuts
        numsticks = length ss
  
main :: IO ()
main = do
  ip <- getContents
  let ss = map read . words . last . lines $ ip
      anss = stickCuts ss
  mapM_ (putStrLn . show) anss
