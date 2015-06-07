-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Maybe

--------------------------------------------------------------------------
--              Data types for my cellular automata
--------------------------------------------------------------------------

-- note that the problem does not allow for empty trees
data Tree a = Leaf a | Branch a (Tree a) (Tree a) deriving (Show, Eq) 

type RuleCA = [Bool]
type TreeCA = Tree Bool

--------------------------------------------------------------------------
--          Functions to operate upon the rule
--------------------------------------------------------------------------

binRepr :: [String]
binRepr = ["0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", 
           "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"] 

intToHex :: Int -> [Int]
intToHex n = if n < 16 then [n] else (reverse $ (n `mod` 16) : reverse (intToHex (n `div` 16)))

-- input is an Int for the rule, output is the actual rule
createRule :: Int -> RuleCA
createRule n = map (\x -> if x == '1' then True else False) . reverse . concat . map (binRepr !!) $ repr 
  where repr = reverse . take 4 $ (reverse $ intToHex n) ++ (repeat 0)

-- given the 4 states of (parent, left, me, right) create my index
createCurStateIndex :: (Bool, Bool, Bool, Bool) -> Int
createCurStateIndex (p, l, m, r) = (8 * cval p) + (4 * cval l) + (2 * cval m) + (cval r)
  where cval x = if x == True then 1 else 0

-- given a rule, and the current states of the 4 cells (p, l, m, r)
-- give the next state of this cell
getNextState :: RuleCA -> (Bool, Bool, Bool, Bool) -> Bool
getNextState rule bvals = rule !! (createCurStateIndex bvals)

--------------------------------------------------------------------------
--          Functions to operate upon the tree
--------------------------------------------------------------------------

treeVal :: TreeCA -> Bool
treeVal (Leaf v)       = v
treeVal (Branch v _ _) = v

simulateAutomataStep :: Maybe Bool -> RuleCA -> TreeCA -> TreeCA
simulateAutomataStep parentv rule (Leaf v)      = 
  let pv = if parentv == Nothing then False else fromMaybe False parentv
      (lv, rv) = (False, False)
  in  Leaf (getNextState rule (pv, lv, v, rv))
simulateAutomataStep parentv rule (Branch v l r) = 
  let pv         = if parentv == Nothing then False else fromMaybe False parentv
      mynewval   = getNextState rule (pv, treeVal l, v, treeVal r)
      mynewleft  = simulateAutomataStep (Just v) rule l
      mynewright = simulateAutomataStep (Just v) rule r
  in  Branch mynewval mynewleft mynewright

automataTrees :: TreeCA -> RuleCA -> [TreeCA]
automataTrees starttree rule = (starttree) : [ simulateAutomataStep Nothing rule ((automataTrees starttree rule) !! (n-1)) | n <- [1..]]

--------------------------------------------------------------------------
--          Functions for parsing
--------------------------------------------------------------------------

createInitTree :: String -> TreeCA
createInitTree = fst . fromMaybe (Leaf False, []) . createInitTree' 

createInitTree' :: String -> Maybe (TreeCA, String)
createInitTree' []            = Nothing
createInitTree' (')': ss)     = Nothing
createInitTree' ('X': ss)     = Just (Leaf True,  ss)  
createInitTree' ('.': ss)     = Just (Leaf False, ss) 
createInitTree' ('(': ss)     =
  let Just (lst, ss')   = createInitTree' ss
      (v : ss'')        = ss'
      Just (rst, ss''') = createInitTree' ss''
      myval             = if v == 'X' then True else False
      mytree            = Branch myval lst rst
  in  Just (mytree, tail ss''')

-- given the current state of the tree, and a string representing path
-- given the current state of the cell specified by the path
getCellValue :: TreeCA -> String -> Bool
getCellValue (Leaf v)          ss    = v
getCellValue (Branch v _ _)   []     = v
getCellValue (Branch _ l _) ('<':ps) = getCellValue l ps
getCellValue (Branch _ _ r) ('>':ps) = getCellValue r ps


--------------------------------------------------------------------------
--                      I/O, Main section, etc.
--------------------------------------------------------------------------

runTestCases :: [TreeCA] -> RuleCA -> Int -> Int -> IO ()
runTestCases _ _ 0 _ = return ()
runTestCases alltrees rule testsrem cursteps = do
  ip <- getLine
  let [nstr, pathstr] = words $ ip
  let newsteps = cursteps + (read nstr)
  let output   = getCellValue (alltrees !! newsteps) (init . tail $ pathstr) 
  putStrLn $ if output == True then "X" else "."
  runTestCases alltrees rule (testsrem-1) newsteps

main :: IO ()
main = do
  rulestr <- getLine
  treestr <- getLine
  teststr <- getLine
  let rule  = createRule (read rulestr)
  let tree  = createInitTree (concat . words $ treestr)
  let tests = read teststr
  let alltrees = (automataTrees tree rule)
  runTestCases alltrees rule tests 0

