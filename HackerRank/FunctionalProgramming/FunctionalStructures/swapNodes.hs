data Tree a = EmptyTree | Node a (Tree a) (Tree a) deriving (Show, Eq)
type ITree = Tree Int

swapNodes :: ITree -> Int -> Int-> ITree
swapNodes EmptyTree     _        _ = EmptyTree 
swapNodes (Node me l r) curdepth k 
  | (curdepth `mod` k /= 0) = Node me (swapNodes l (curdepth + 1) k) (swapNodes r (curdepth + 1) k) -- No swap
  | otherwise               = Node me (swapNodes r (curdepth + 1) k) (swapNodes l (curdepth + 1) k) -- Swap!!

-- input nodes are specified in level-order (BFS)
-- start consuming the input from the end, building leaves, and then nodes
-- and all the while keep pushing them onto a queue of trees
-- consume from the queue if current nodes are not -1
buildTree ::[ITree] -> [[Int]] -> ITree
buildTree []       []  = Node 1 (EmptyTree) (EmptyTree)
buildTree subtrees []  = Node 1 (head subtrees) (last subtrees)
buildTree subtrees nss = 
  let emptyRight = (last . last $ nss) == -1
      emptyLeft  = (head . last $ nss) == -1
      rst        = Node (last . last $ nss) (last . init $ subtrees) (last subtrees)
      lst        = if emptyRight then Node (head . last $ nss) (last . init $ subtrees) (last subtrees)                               --same subtrees as rst
                                 else Node (head . last $ nss) (last . init . init . init $ subtrees) (last . init . init $ subtrees) --take 2 new subtrees
      nodesToDrop= if emptyLeft || emptyRight then 2 else 4
      recursests = reverse . drop nodesToDrop . reverse $ subtrees
      recursenss = init nss     -- the two numbers are always consumed from the last row of nss
  in  if emptyLeft && emptyRight  
         then buildTree (EmptyTree : EmptyTree : subtrees) recursenss
         else if emptyRight       
                 then buildTree (lst : EmptyTree : recursests) recursenss
                 else if emptyLeft
                         then buildTree (EmptyTree : rst : recursests) recursenss
                         else buildTree (lst : rst : recursests) recursenss

inOrderTraverse :: ITree -> [Int]
inOrderTraverse EmptyTree     = []
inOrderTraverse (Node me l r) = inOrderTraverse l ++ [me] ++ inOrderTraverse r

-----------------------------------------------------------------------------
--      Functions for parsing, printing results, etc (impure)
-----------------------------------------------------------------------------

printBinTree :: ITree -> IO ()
printBinTree tree = putStrLn $ unwords . map show . inOrderTraverse $ tree

runTestCases :: [Int] -> ITree -> IO ()
runTestCases []     _    = return ()
runTestCases (n:ns) tree = do
  let newTree = swapNodes tree 1 n
  printBinTree newTree
  runTestCases ns newTree

main :: IO ()
main = do
  ip <- getContents
  let is    = lines ip 
      nnl   = read . head $ is
      tndss = map (map read . words) . take nnl . tail $ is
      tree  = buildTree [] $ tndss
      ntc   = head . drop nnl . tail $ is
      tcs   = map read . tail . drop nnl . tail $ is
  runTestCases tcs tree
