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
  
