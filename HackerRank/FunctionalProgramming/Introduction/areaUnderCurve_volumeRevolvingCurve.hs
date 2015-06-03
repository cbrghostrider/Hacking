import Text.Printf (printf)
import Data.List

delta :: Double
delta = 0.001

areaCircle :: Double -> Double
areaCircle r = pi * r * r

areaDisk :: Double -> Double
areaDisk rad = delta * areaCircle rad

areaRect :: Double -> Double
areaRect = (delta *)

evalAtX ::  [Int] -> [Int] -> Double ->  Double
evalAtX as bs xc = sum . map (\(ac, bc) -> ac * (xc ** bc)) $ zip (map fromIntegral as) (map fromIntegral bs)  

sequenceVals :: Int -> Int -> [Double]
sequenceVals l r = unfoldr (\seed -> if seed > (fromIntegral r) then Nothing else Just(seed, (seed + delta))) (fromIntegral l)

solve :: Int -> Int -> [Int] -> [Int] -> [Double]
solve l r as bs = 
  let xs  = sequenceVals l r
      hts = map (evalAtX as bs) $ xs
      rds = map (\h -> (areaRect h, areaDisk h)) $ hts
      area   = sum . map fst $ rds
      volume = sum . map snd $ rds
  in  [area, volume]

main :: IO ()
main = getContents >>= mapM_ (printf "%.1f\n"). (\[a, b, [l, r]] -> solve l r a b). map (map read. words). lines
