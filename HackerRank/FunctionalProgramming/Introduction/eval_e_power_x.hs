-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
factorial :: Int -> Int
factorial 0 = 1
factorial n = n * factorial (n-1)

solve :: Double -> Double
solve x = sum . map (\n -> (x ** (fromIntegral n)) / (fromIntegral . factorial $ n))$ [0..9]

main :: IO ()
main = getContents >>= mapM_ print. map solve. map (read::String->Double). tail. words

