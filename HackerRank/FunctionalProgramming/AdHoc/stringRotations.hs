import Data.List

solveProblem :: String -> [String]
solveProblem []  = []
solveProblem [x] = [[x]]
solveProblem str = take (length str) $ unfoldr (\ss -> let rs = (tail ss ++ [head ss]) in Just (rs, rs)) str

main :: IO () 
main = do
  inputs <- getContents
  putStrLn $ unlines . map unwords . map solveProblem . tail . lines $ inputs
