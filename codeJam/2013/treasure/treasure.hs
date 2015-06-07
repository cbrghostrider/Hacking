-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 
import Data.Monoid

-- Let Sa denote the set of available keys I have at any point in the problem
--
-- Theorem 1: If I use a key k (belongs to Sa) to open a chest Ci, and
--            that chest immediately gives me back key k (one or more copies),
--            then I can only make the current situation better (or same) by
--            opening this chest. These are Tier 1 chests.
-- Theorem 2: If I have n chests remaining that need n copies of key k (belong to Sa) 
--            to open them, and I already have n copies of k in Sa, then I can
--            open any and all of these chests with no harm. These are tier 2 chests.
-- Theorem 3: Say I have a chest Ci, that needs key k (belongs to Sa) to be opened.            
--            Even if this chest does not give me back key k immediately, it *may*
--            be safe to open. This is only true if key k is ultimately *reachable*
--            from this chest. Which means, opening this chest, gives some new keys
--            which in turn open new chests, which give new keys...so on- such that
--            finally I get back key k. (I call this ultimateSet in the code)

-- Note [1]: My initial solution to the problem consisted of the following greedy solution
-- At each step, classify all the currently closed chests into 5 tiers
-- Then pick the first possible chest that I can open currently, thus picking
-- the best tier possible.
--
-- Note [2]: This solution worked fine, but the problem had one INCREDIBLY ANNOYING requirement
-- If multiple correct solutions were possible, I had to output the "lexicographically smallest" solution
-- This requirement caused me lot of grief, because my tier centric solution
-- preferred tier x solutions over tier y solutions (for x<y) . In other words, 
-- I always picked the "tier-icographically smallest solution" 
-- Ultimately I had to merge my pretty tier centric solution (T1, T2, T3, into T123) 
-- and clobber the code a bit to satisfy this requirement :)

type Key     = Int
type Chest   = (Int, Key, [Key])     -- chnum, key to open me, keys I provide
type Problem = ([Key], [Chest])      -- keys I start with, and chests I start with
type Result  = Maybe [Int]           -- sequence of chests I should open
data ChTier  = CT1 |  -- Tier 1 chests are those that need key k to open, and offer key k inside
               CT2 |  -- Tier 2 chests are those that need key k to open, and the only such ones left
               CT3 |  -- Tier 3 chests are those that if opened with k now, will yield k in their ultimateSet
               CT4 |  -- Tier 4 chests are those that can be opened with k now, but will NOT yield k in their ultimateSet
               CTN    -- Tier N chests are those that cannot be opened now (but may be in the future)
               deriving (Show, Eq, Ord)

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
writeResult Nothing = "IMPOSSIBLE" 
writeResult (Just r)= unwords . map show $ r

parseChest :: (Int, String) -> Chest
parseChest (cn, cstrs) = 
  let cnums = map read . words $ cstrs
      myK   = head cnums
      myN   = head . tail $ cnums
      ks    = if myN == 0 then [] else tail . tail $ cnums
  in  (cn, myK, ks)

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (kn:ss) = 
  let n  = last . map read . words $ kn
      ks = map read . words . head $ ss
      cs = map parseChest . zip [1..] . take n . tail $ ss
      ss'= drop n . tail $ ss
  in  (ks, cs) : parseProblem ss'

chestTier1 :: [Key] -> [Chest] -> Chest -> Bool
chestTier1 ks cs chest@(n, k, chks) = (k `elem` ks) && (k `elem` chks)

chestTier2 :: [Key] -> [Chest] -> Chest -> Bool
chestTier2 ks cs chest@(n, k, chks) = (k `elem` ks) && (lenchk < lenavail ||(lenavail == lenchk && lenct1 == 0))
  where lenchk = (length . filter (not . chestTier1 ks cs) . filter (\(_, ck,  _) -> ck == k) $ cs )
        lenavail = length . filter (==k) $ ks
        lenct1 = (length . filter (chestTier1 ks cs) . filter (\(_, ck,  _) -> ck == k) $ cs )

chestTier3 :: [Key] -> [Chest] -> Chest -> Bool
chestTier3 ks cs chest@(n, k, chks) = k `elem` computeUltimateSet (cs \\ [chest]) (chks ++ (ks \\ [k]))

chestTierN :: [Key] -> [Chest] -> Chest -> Bool
chestTierN ks cs chest@(n, k, chks) = not (k `elem` ks)

-- takes current list of keys available and current list of unopened chests, 
-- and a candidate chest to classify, and tells us its tier
computeChestTier :: [Key] -> [Chest] -> Chest -> ChTier
computeChestTier ks cs chest@(n, k, chks) 
  | chestTier1 ks cs chest = CT1
  | chestTier2 ks cs chest = CT2
  | chestTierN ks cs chest = CTN
  | chestTier3 ks cs chest = CT3
  | otherwise              = CT4
  
-- given a key set accks, computes all keys that are ultimately reachable from it
-- this includes direct and indirect keys
-- terminates when the ultimate set is the input set
computeUltimateSet :: [Chest] -> [Key] -> [Key]
computeUltimateSet cs accks = 
  let newks = concat . map (\(_, _, cks) -> cks) . filter (\(_, k, _) -> k `elem` accks) $ cs
      recks = nub $ newks ++ accks
  in  if recks == accks then accks else computeUltimateSet cs recks

computeChestTiers :: Problem -> ([Chest], [Chest], [Chest])
computeChestTiers (ks, cs) = 
  let ts  = map (computeChestTier ks cs) cs
      tcs = sortBy (comparing fst) $ zip ts cs
      (t1cs, rs) = span ((== CT1) . fst) $ tcs
      (t2cs, rs') = span ((== CT2) . fst) $ rs
      (t3cs, rs'') = span ((== CT3) . fst) $ rs'
      (t4cs, rs''') = span ((== CT4) . fst) $ rs''
      tncs = rs'''
      lexiOrd = sortBy (comparing (\(n, _, _) -> n)) . map snd
      -- Please see note 2 for why I merged these 3 tiers
  in  ((lexiOrd $ t1cs ++ t2cs ++ t3cs), lexiOrd t4cs, lexiOrd tncs)

solveProblem :: Problem -> Result
solveProblem (ks, []) = Just []
solveProblem (ks, cs) = 
  let (t123s, t4s, tns) = computeChestTiers (ks, cs)
      chosencs   = if (not.null $ t123s) then (Just . head $ t123s) else if (not . null $ t4s) then (Just . head $ t4s) else Nothing
      chosencs'  = fromMaybe (0, 0, []) chosencs
      reccs      = cs \\ [chosencs']
      chosenKey  = (\(_, k, _) -> k) chosencs'
      chosenNum  = (\(n, _, _) -> n) chosencs'
      freedKeys  = ((\(_, _, kcs)->kcs) chosencs')
      recks      = (ks \\ [chosenKey]) ++ freedKeys
      recresults = solveProblem (recks, reccs)
  in  if chosencs == Nothing then Nothing else recresults >>= \ress -> Just (chosenNum : ress)
  

