import Data.Bits
import Data.List

combos :: [Int] -> [(Int, Int)]
combos [] = []
combos (x:xs) = combos' x xs
  where combos' _ [] = []
        combos' x (y:ys) = (x, y) : combos' x ys

maxXor :: Int -> Int -> Int
maxXor l r = maximum . map (\(x, y) -> x `xor` y) . concat . map (\(x:xs) -> map (\y -> (x, y)) (x:xs)) . init . tails $ [l, l+1..r]

main :: IO ()
main = do
  l <- readLn
  r <- readLn
  print $ maxXor l r
