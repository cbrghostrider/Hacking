-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

solveProblem :: Int -> String
solveProblem n = 
  let cands  = [(x, n-x) | x <- [n, (n-1)..0], x `mod` 3 == 0, (n-x) `mod` 5 == 0]
      choice = head cands
  in  if null cands then "-1" else (concat . map show $ (replicate (fst choice) 5) ++ (replicate (snd choice) 3))

runTests :: Int -> IO ()
runTests 0 = return ()
runTests n = do
  nstr <- getLine
  let ans = solveProblem (read nstr)
  putStrLn ans
  runTests (n-1)

main :: IO ()
main = do
  tcstr <- getLine
  runTests (read tcstr)
