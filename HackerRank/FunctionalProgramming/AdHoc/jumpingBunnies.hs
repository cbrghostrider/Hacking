import Data.List

lcmlist :: [Int] -> Int
lcmlist = foldl1' (\alcm num -> lcm alcm num)

main :: IO ()
main = do
  _     <- getLine
  nsstr <- getLine
  putStrLn $ show $ lcmlist (map read . words $ nsstr)
