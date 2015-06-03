factorial :: Int -> Int
factorial 0 = 1
factorial n = n * factorial (n-1)

solve :: Double -> Double
solve x = sum . map (\n -> (x ** (fromIntegral n)) / (fromIntegral . factorial $ n))$ [0..9]

main :: IO ()
main = getContents >>= mapM_ print. map solve. map (read::String->Double). tail. words

