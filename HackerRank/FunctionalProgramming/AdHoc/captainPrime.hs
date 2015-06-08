-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-------------------------------------------------------------------------------
-- Credit : The following (efficient) sieve is not my code
primes n = sieve $ 2:[3,5..n] where
      sieve (p:xs) | p*p > n = xs
                   | True = p:sieve [x | x <- xs, mod x p /= 0]
-- End credit.        
-------------------------------------------------------------------------------

data SailorType = LEFT | RIGHT | CENTRAL | DEAD deriving (Show, Eq)

leftSubSeqsValid :: [Int] -> String -> Bool
leftSubSeqsValid _ [] = True
leftSubSeqsValid ps cs = ((read cs) `elem` ps) && leftSubSeqsValid ps (tail cs)

rightSubSeqsValid :: [Int] -> String -> Bool
rightSubSeqsValid _ [] = True
rightSubSeqsValid ps cs = ((read cs) `elem` ps) && rightSubSeqsValid ps (init cs)

classifySailor ::[Int] -> String -> SailorType
classifySailor ps sailor = 
  let lss = leftSubSeqsValid ps sailor
      rss = rightSubSeqsValid ps sailor
  in  if '0' `elem` sailor then DEAD else if lss && rss then CENTRAL else if lss then LEFT else if rss then RIGHT else DEAD

main :: IO ()
main = do
  ip <- getContents
  let ss = tail . lines $ ip
  let primeNums = primes (1000000) --limit for problem
  let anss = map (classifySailor primeNums) $ ss
  mapM_ (putStrLn . show) anss

