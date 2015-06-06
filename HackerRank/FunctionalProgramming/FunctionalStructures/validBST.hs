import Data.Maybe
import Data.List

data Tree a = EmptyTree | Node a (Tree a) (Tree a) deriving (Show, Eq)
type ITree = Tree Int

allTreeCombos :: Int -> [ITree] -> [ITree] -> [ITree]
allTreeCombos me lts rts = [(Node me ltree rtree) | ltree <- lts, rtree <- rts]

compileValidTrees :: Int -> [Int] -> [Int] -> [ITree]
compileValidTrees me lhsns rhsns = 
  let lts   = constructTrees lhsns 
      rts   = constructTrees rhsns
      lhsok = lhsns == [] || me >= maximum lhsns
      rhsok = rhsns == [] || me <= minimum rhsns
  in  if lhsok && rhsok then allTreeCombos me lts rts else []

-- gives all possible VALID binary trees for this sequence
constructTrees :: [Int] -> [ITree]
constructTrees [] = [EmptyTree]
constructTrees ns = 
  let me      = head ns
      myTrees = foldl' (\accts n ->  accts ++ compileValidTrees me (take n . tail $ ns) (drop n . tail $ ns) ) [] $ [0..(length . tail $ ns)]
  in  myTrees

solveProblem :: [Int] -> String
solveProblem ns = let candts = constructTrees ns in if null candts then "NO" else "YES"

runTests :: Int -> IO ()
runTests 0 = return ()
runTests n = do
  nnds <- getLine
  nds  <- getLine
  let nodes = map read . words $ nds
  putStrLn $ solveProblem nodes
  runTests (n-1)

main :: IO ()
main = do
  ntc <- getLine
  runTests (read ntc)
