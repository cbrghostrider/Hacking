import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 

type Problem = (Int, [Int])
type Result  = Int 

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

writeOutput :: [(Int, Result)] -> [String]
writeOutput = map (\(i, r) -> ("Case #" ++ (show i) ++ ": " ++ (writeResult r)))

processInput :: String -> String
processInput = unlines . writeOutput . zip [1..] . map solveProblem . parseProblem . tail . lines

writeResult :: Result -> String
writeResult = show

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (ns:ms:ss)  = (n, (map read . words $ ms)) : parseProblem ss
  where [b, n] = map read . words $ ns

-- returns chosen barber index (0 indexed), and all new times 
useFirstFreeBarber :: [(Int, Int)] -> (Int, [Int])
useFirstFreeBarber crs =
  let crsInit  = takeWhile ((/=0). fst) crs
      crs'     = dropWhile ((/=0) . fst) crs
      myBarber@(_, myr) = head crs'
      crsLater = tail crs'
  in  if null crs' -- no barber free
         then error "Something went wrong"
         else (length crsInit , (map fst crsInit) ++ [myr] ++ (map fst crsLater) )

-- given a list of barbers (time to completion)
-- makes one barber free, and decrements everyone elses time
makeBarberFree :: [Int] -> [Int]
makeBarberFree cs = 
  let alreadyFree = not . null . filter ((==0) ) $ cs
      ctime = minimum cs
  in  if alreadyFree then cs else map (subtract ctime) cs

-- given barbers (current times to completion, and reset times)
-- finishes one barber (if needed), and decrements others counts (if needed)
-- and returns (the barber that finished, new times to completion for all)
simulateHairCut :: [(Int, Int)] -> (Int, [Int])
simulateHairCut crs = 
  let newcs = makeBarberFree (map fst crs)
  in  useFirstFreeBarber (zip newcs (map snd crs))

solveProblem :: Problem -> Result
solveProblem pb@(n, ms) =
  let initProb = zip (repeat 0) ms  -- barbers (times-to-completion, reset-times) 
      result = foldr (\_ (_, pb) -> let (barb, newcs) = simulateHairCut pb in (barb, zip newcs ms)) (0, initProb)$ [1..n]
  in  1 + (fst result)


