-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

changeStr :: String -> String
changeStr ss = foldl' (\acc c-> if c == head acc then acc else c:acc) [head ss] $ tail ss

main :: IO ()
main = do
  ip <- getContents
  let ss = tail . lines $ ip
  let cs = map changeStr ss
  mapM_ (putStrLn . show) $ map (\(sp, sn) -> (length sp) - (length sn)) $ zip ss cs
