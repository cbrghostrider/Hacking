import Data.List

unfoldFunc :: [Int] -> Maybe ([Int], [Int])
unfoldFunc seed = Just (newseed, newseed)
  where newseed = (interimList) ++ [1]
        interimList = map fst . tail $ scanl (\acc@(af, as) n -> (as + n, n)) (0, 0) seed

solveProblem :: Int -> [[Int]]
solveProblem 1 = [[1]]
solveProblem 2 = [[1], [1, 1]]
solveProblem n = (solveProblem 2) ++ (take (n-2) $ unfoldr (\seed -> unfoldFunc seed) (last . solveProblem $ 2))

main :: IO ()
main = do
  nstr <- getLine
  putStrLn (unlines . map unwords . map (map show) . solveProblem . read $ nstr)
