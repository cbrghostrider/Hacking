import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 

type Node    = Int
type Edge    = (Int, Int)
type Problem = ([Node], [Edge])
type Result  = Int 
data Tree a  = EmptyTree | TreeNode a [Tree a] deriving (Eq, Show, Read)

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
parseProblem (nn:ss)  = ([1..num], edges) : (parseProblem . drop (num-1) $ ss)
  where num   = read nn 
        edges = map ((\[n1, n2] -> (n1, n2)) . map read . words) . take (num - 1) $ ss

-- creates tree rooted at Node
compileTree :: Node -> Problem -> (Tree Node, Problem)
compileTree n pb@(ns, es) =
  let myes         = filter (\(n1, n2) -> n1 == n || n2 == n) $ es
      myns         = map (\(n1, n2) -> if n1 == n then n2 else n1) $ myes
      accpb        = (ns \\ myns, es \\ myes)
      (ts, pb')    = foldr (\nd (tls, pblm) -> let (newt, newp) = compileTree nd pblm 
                                               in  (newt:tls, newp))
                           ([], accpb) $ myns
  in  if null myes || null myns 
         then (TreeNode n [], pb )
         else (TreeNode n ts, pb')

-- converts the tree into a full BT
-- and returns the number of Nodes in it
convertBinTree :: Tree Node -> Int
convertBinTree EmptyTree = 0
convertBinTree (TreeNode n ts) = 
  let myConvTrees = reverse . sort . map convertBinTree $ ts
      mySubtrees  = take 2 myConvTrees
  in  if length ts == 0 
         then 1 -- for myself
         else if length ts < 2
                 then 1 -- delete my child
                 else 1 + sum mySubtrees -- length ts >= 2

solveProblem :: Problem -> Result
solveProblem pb@(ns, es) =
  let nps       = map (\n -> (n, (ns \\ [n], es))) $ ns
      initTrees = map (\(n, p) -> (fst $ compileTree n p)) $ nps
      sizes     = reverse . sort . map convertBinTree $ initTrees
  in  if null ns || null sizes
         then error "Oops, something went wrong!"
         else (length ns) - (head sizes)
  


