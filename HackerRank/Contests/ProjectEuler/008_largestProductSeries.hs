-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Char

-- Project Euler: Problem 8
ans8 :: String -> Int -> Int
ans8 str k = maximum . map product . map (\v -> take k . drop v $ ds) $ [0..(n-k)]  
  where ds = map digitToInt str
        n  = length ds
        
splitList :: [String] -> [(String, String)]
splitList [] = []
splitList (s1:s2:ss) = (s1, s2) : splitList ss

xlateVals :: (String, String) -> (Int, String)
xlateVals (nk, nstrs) = ((read . last . words $ nk), nstrs)

main :: IO ()
main = do 
  ip <- getContents
  let allvs = tail . lines $ ip
      svs   = splitList allvs
      kns   = map xlateVals svs
  mapM_ (putStrLn . show) $ map (\(k, str) -> ans8 str k) kns
