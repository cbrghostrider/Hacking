-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import System.Environment (getArgs)
import Data.Maybe

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

type Price     = Int

-- item with price p exists or not (for optimization)
-- currently just going with price
type Inventory = [Price]

-- a bundle of (Credit, Inventory)
type Bundle    = (Price, Inventory)
type Bundles   = [Bundle]

bundleThreeLines :: [[String]] -> [String] -> [[String]]
bundleThreeLines rbss [] = rbss
bundleThreeLines rbss (x1:x2:x3:xs) = bundleThreeLines (rbss ++ [[x1, x2, x3]]) xs
bundleThreeLines _ _ = error "Malformed input: Not enough lines of sets of 3"

-- takes a bundle, and returns a maybe pair of items that add up to credit
getExactMatch :: Bundle -> Maybe (Price, Price)
getExactMatch b@(c, []) = Nothing
getExactMatch b@(c, (x:xs)) = let other = c - x in if other `elem` xs then Just (x, other) else getExactMatch (c, xs)

getIndex :: Bundle -> (Int, Int) -> (Int, Int)
getIndex b (x, y) = (\[x', y'] -> (x', y')) . map fst . take 2 . filter ((== True) . snd) . zip [1..] . map (\p -> p == x || p == y) $ snd b

processInput :: String -> String
processInput ip = 
  let nBundles  = (read . head . lines $ ip)::Int
      bundles   = foldl (\a [c, ni, items] -> a ++ [((read c), (map read . words $ items))]) ([]::Bundles) . bundleThreeLines [] . tail . lines $ ip
      solns     = map (fromMaybe (0, 0)) . map getExactMatch $ bundles 
      solnInds  = map (\(x, y) -> if x>y then (y, x) else (x, y)) . map (\((x, y), b) -> getIndex b (x, y)) . zip solns $ bundles
      solnStrs  = map (\(n, (x, y)) -> "Case #" ++ (show n) ++ ": " ++ (show x) ++ " " ++ (show y)) . zip [1..] $ solnInds 
  in  unlines solnStrs


