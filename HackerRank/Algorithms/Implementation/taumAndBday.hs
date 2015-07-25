-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
runTests :: Int -> IO ()
runTests 0 = return ()
runTests tc = do
  bwstr  <- getLine
  xyzstr <- getLine
  let [b, w]    = map read . words $ bwstr
      [x, y, z] = map read . words $ xyzstr
      costBlack = minimum [x, y+z]
      costWhite = minimum [y, x+z]
      total     = b * costBlack + w * costWhite
  putStrLn (show total)
  runTests (tc-1)

main :: IO ()
main = do
  tcstr <- getLine
  runTests (read tcstr)
