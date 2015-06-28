-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import qualified Data.Map as M
import Data.List (foldl')

isAnagramPalin :: String -> String
isAnagramPalin "" = "YES"
isAnagramPalin ss = 
  let mymap  = M.empty
      finmap = foldl' (\macc c -> let res = M.lookup c macc 
                                  in  if res == Nothing 
                                         then M.insert c 1 macc
                                         else let (Just v) = res in M.insert c (v+1) macc) mymap ss
      vals   = M.elems finmap
      odds   = filter ((/= 0) . (`mod` 2)) vals
  in  if length odds <= 1 then "YES" else "NO"

main :: IO ()
main = do
  ip <- getContents
  putStrLn $ isAnagramPalin ip
