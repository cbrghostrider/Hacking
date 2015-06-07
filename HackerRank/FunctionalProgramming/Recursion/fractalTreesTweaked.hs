-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

numRows :: Int
numRows = 63

numCols :: Int
numCols = 100

fillUnderScores :: [[Char]] -> [[Char]]
fillUnderScores css = css ++ (take (numRows - length css) $ repeat (take numCols $ repeat '_'))

emitOnesAtPos :: Int -> Int -> [[Int]]
emitOnesAtPos lenSeq pos = take lenSeq $ repeat [pos]

onesPosForYArms :: Int -> Int -> [[Int]]
onesPosForYArms lenSeq lastPos = take lenSeq $ unfoldr (\ls -> let ss = [head ls - 1, last ls + 1] in Just (ss, ss)) [lastPos]

fractalYArms :: Int -> Int -> [[Int]]
fractalYArms lenSeq pos = (emitOnesAtPos lenSeq pos) ++ (onesPosForYArms lenSeq pos)

combineTwoFractals :: [[Int]] -> [[Int]] -> [[Int]]
combineTwoFractals = zipWith (++)

numOnes :: [Int]
numOnes = [16, 8, 4, 2, 1]

fractalize :: Int -> Int -> [[Int]]
fractalize pos iter = 
  let myones = numOnes !! (iter - 1)
      mycss  = fractalYArms myones pos
      (recFracLeft, recFracRight) = (fractalize (head . last $ mycss)  (iter-1), fractalize (last . last $ mycss) (iter-1))
      moreRows = combineTwoFractals recFracLeft recFracRight
  in  if iter == 0 then [] else mycss ++ moreRows

lineToChars :: [Int] -> [Char]
lineToChars os = map (\n -> if n`elem` os then '1' else '_') $ [1..numCols]

main :: IO ()
main = do
  nstr <- getLine 
  let css = map lineToChars . reverse $ fractalize (numCols `div` 2) (read nstr)
  putStrLn $ unlines css

