-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
main :: IO ()
main = do
  ip <- getLine
  let [a, b, n] = (map read . words . head . lines $ ip)::[Integer]
      modFibo   = a : b : zipWith (\num np1 -> np1*np1+num) modFibo (tail modFibo)
  putStrLn . show $ modFibo !! (fromIntegral $ n-1)
