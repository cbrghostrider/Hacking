-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
merge :: String -> String -> String
merge s1 s2 = concat $ zipWith (\c1 c2 -> [c1, c2]) s1 s2

main :: IO ()
main = do
  s1 <- getLine 
  s2 <- getLine
  putStrLn $ merge s1 s2
