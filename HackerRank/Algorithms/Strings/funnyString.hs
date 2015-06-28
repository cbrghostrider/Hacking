-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Char (ord)

funnyStr :: String -> String
funnyStr ss = 
  let rs = reverse ss
      sos = map ord ss
      ros = map ord rs
      svs = zipWith (\x y -> abs $ x - y) (tail sos) (init sos)
      rvs = zipWith (\x y -> abs $ x - y) (tail ros) (init ros)
  in  if svs == rvs then "Funny" else "Not Funny"

main :: IO()
main = do
  ip <- getContents
  let ss = tail . lines $ ip
  mapM_ (putStrLn) $ map funnyStr ss 
