import Data.List
-- (R, G, Y, B)

foldFunc :: (Bool, Int, Int, Int, Int) -> Char -> (Bool, Int, Int, Int, Int)
foldFunc (abv, arn, agn, ayn, abn) colorCh =
  let (irn, ign, iyn, ibn)
        | colorCh == 'R' = (arn+1, agn, ayn, abn)
        | colorCh == 'G' = (arn, agn+1, ayn, abn) 
        | colorCh == 'Y' = (arn, agn, ayn+1, abn) 
        | colorCh == 'B' = (arn, agn, ayn, abn+1)
      diffrg = abs (irn - ign)
      diffyb = abs (iyn - ibn)
  in if diffrg > 1 || diffyb > 1 
        then (False, irn, ign, iyn, ibn)
        else (abv,   irn, ign, iyn, ibn)

solveProblem :: String -> Bool
solveProblem ss =  
  let foldResults@(bv, rn, gn, yn, bn) = foldl' (foldFunc) (True, 0, 0, 0, 0) ss
  in  bv == True && rn == gn && yn == bn

runTestCases :: Int -> IO ()
runTestCases 0 = return ()
runTestCases n = do
  ss <- getLine
  putStrLn $ show . solveProblem $ ss
  runTestCases (n-1)

main :: IO ()
main = do 
  tcs <- getLine
  runTestCases (read tcs)
