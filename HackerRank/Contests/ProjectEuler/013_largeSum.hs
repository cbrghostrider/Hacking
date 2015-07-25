-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Char

chrToInt :: Char -> Int
chrToInt x = ord x - ord '0'

transpose' :: [[a]] -> [[a]]
transpose' xss 
  | ( and . map null $ xss ) == True = []
  | otherwise = (map head $ xss) : (transpose' . map tail $ xss)

collapseMatrix :: [[Int]] -> [Int]
collapseMatrix xss = (map chrToInt . show $ fcarry) ++ fpss
  where
    (fcarry, fpss) = foldl foldFunc (0, []) (reverse . map sum . transpose' $ xss)
    foldFunc = (\ (carry, ns) x -> ((x + carry) `div` 10, ((x + carry) `mod` 10) : ns)) 

main :: IO ()
main = interact $ take 10 . concat . map show . collapseMatrix . map (map chrToInt) . tail . lines 
