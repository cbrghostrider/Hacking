-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Control.Monad
import Data.List

growSpring :: Int -> Int
growSpring = (*2)

growSummer :: Int -> Int
growSummer = (+1)

solveProblem :: Int -> Int 
solveProblem n = foldl' (\ac f -> f ac) 1 . take n . concat . repeat $ [growSpring, growSummer]

main = do
  n <- readLn :: IO (Int)
  allLines <- replicateM n getLine
  let answers = map (solveProblem . read) $ allLines
  mapM_ print answers
  
