fibonacciNums :: [Integer]
fibonacciNums = 0 : 1 : zipWith (+) fibonacciNums (tail fibonacciNums)

main :: IO ()
main = do
  ip <- getContents
  let ns = map read . tail . lines $ ip
  mapM_ (putStrLn . show) $ map ((`mod` (10^8 + 7)) . (fibonacciNums !!)) ns
