-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-- algorithmic complexity is O(1) for the solution!
-- small input works fine, 
-- but for big input, there are some rounding issue w/ interconversions
-- between big integer and double types
-- TODO: Figure out how to fix bug that happens occasionally on large input
import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 

type Problem = (Integer, Integer) -- (r, t)
type Result  = Integer 

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

writeOutput :: [(Int, Result)] -> [String]
writeOutput = map (\(i, r) -> ("Case #" ++ (show i) ++ ": " ++ (writeResult r)))

processInput :: String -> String
processInput = unlines . writeOutput . zip [1..] . map solveProblem . parseProblem . tail . lines

writeResult :: Result -> String
writeResult = show

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (ns:ss)  = (r, t) : parseProblem ss
  where rs' = map read . words $ ns
        r   = head rs'
        t   = last rs'

-- area of ring is pi ((r + 2i + 1)^2 - (r + 2i)^2)
-- which simpliies to pi (2r + 4i + 1)
-- since pi area takes 1 ml of paint, 
-- the above will take (2r + 4i + 1) ml of paint
-- paintForRing :: Integer -> Integer -> Integer
-- paintForRing r i = (2 * r + 4 * i + 1)

-- if I can draw n rings (counting from 0), then amount of paint consumed = sum from i = 0 to n 
-- of paintForRing r i
-- sumOverI (2r + 4i + 1)
-- (2r + 1)(n+1) + 4n(n+1)/2 
-- this is equal to t
-- 4n^2 + n (4r + 2 + 4) + (4r + 2) = 2t
-- 4n^2 + n (4r + 6) + (4r + 2 - 2t) = 0
-- a = 4
-- b = 4r+6
-- c = 4r + 2 - 2t
-- solving quadratic equation for n
-- (-b +- sqrt(b^2 - 4ac)) / 2a
-- simplifies to (sqrt ( (4r+6)^2 - (4 * 4 * (4r + 2 - 2t))) - (4r + 6)) / 8
solveProblem :: Problem -> Result
solveProblem (r, t) =
  let fRP6 = 4 * r + 6
      fRP6S= fRP6^2
      fourac= 4 * 4 * (4*r + 2 - 2*t)
      nume = (sqrt . fromIntegral $ fRP6S - fourac) - (fromIntegral fRP6)
      deno = fromIntegral 8
      ans  = nume / deno
  in  floor (ans + 1 )

