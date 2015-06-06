import Data.List
import Data.Ord

findGcd :: [(Int, Int)] -> [(Int, Int)] -> [(Int, Int)]
findGcd n1pps n2pps = 
  let ips    = map fst $ intersectBy (\(b1, e1) (b2, e2) -> b1 == b2) n1pps n2pps
      n1pps' = sortBy (comparing fst) . filter ((`elem` ips) . fst) $ n1pps
      n2pps' = sortBy (comparing fst) . filter ((`elem` ips) . fst) $ n2pps
  in  map (\((b1, e1), (_, e2)) -> (b1, min e1 e2)) $ zip n1pps' n2pps'

convertToNumStr :: [(Int, Int)] -> String
convertToNumStr []  = "2 0"
convertToNumStr pps = unwords . map show . concat . map (\(b, e) -> [b, e]) $ pps

solveProblem :: [[(Int, Int)]] -> String
solveProblem = convertToNumStr . foldl1' (\gcdpps npps -> findGcd gcdpps npps)  

splitEvery :: Int -> [Int] -> [[Int]]
splitEvery k ns
  | length ns <= k = [ns]
  | otherwise      = (take k ns) : splitEvery k (drop k ns)

main :: IO()
main = do
  ip <- getContents
  let nss  = map (map read . words) . tail . lines $ ip
  let ppss = map (map (\[a, b] -> (a, b)) . splitEvery 2) nss
  putStrLn $ solveProblem ppss
