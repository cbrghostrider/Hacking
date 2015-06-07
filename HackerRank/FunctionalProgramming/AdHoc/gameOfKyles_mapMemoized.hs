-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-- Memoized with Data.Map... still taking too long! ... 8m 37 sec on test case 2.
import Data.List
import Data.Ord
import qualified Data.Map as M

type CacheMap = M.Map String Bool

-- take batches of pin collections, and stitches them together with an X in between
compileMemoString :: [String] -> String
compileMemoString [] = []
compileMemoString ss = foldl1' (\accstr batch -> accstr ++ "X" ++ batch) $ ss

-- groups the pins into batches of contiguous standing pins (eating Xs)
simplifyPins :: String -> [String]
simplifyPins = sortBy (comparing length) . filter  (/= []) . foldr (foldPins) [[]]
  where 
    foldPins = \pin accps -> if pin == 'X' then ([]:accps) else (pin : head accps) : tail accps

knockOneOut :: [String] -> Int -> [[String]]
knockOneOut pss seqnum = 
  let chosens = pss !! seqnum
      prior   = take seqnum pss
      later   = drop (seqnum + 1) pss
      limit   = ((length chosens) `div` 2) + ((length chosens) `mod` 2) 
      currss  = map (\n -> filter (/= []) [drop (n+1) chosens, take n chosens]) . take limit $[0..]
      retss   = map (sortBy (comparing length)) . map (\seq -> prior ++ seq ++ later) $ currss
  in  if length chosens == 1 then if null prior && null later then [] else [prior ++ later] else retss

knockTwoOut :: [String] -> Int -> [[String]]
knockTwoOut pss seqnum = 
  if length (pss !! seqnum) == 2
     then if length pss == 1 
             then []
             else [(take seqnum pss) ++ (drop (seqnum+1) pss)] 
     else knockOneOut ((take seqnum pss) ++ [tail $ (pss !! seqnum)] ++ (drop (seqnum + 1) pss)) seqnum

-- take a sequence of pins, and knocks out exactly 1 from exactly 1 batch
-- or knocks out exactly 2 contiguous from exactly 1 batch
-- and returns all such results
compilePossibilities :: [String] -> [[String]]
compilePossibilities pss = 
  let knock1Outss = concat . map (\seqnum -> knockOneOut pss seqnum) $ [0..(length pss - 1)]
      knock2Outss = concat . map (\seqnum -> knockTwoOut pss seqnum) . filter (\seqnum -> length (pss !! seqnum) >= 2) $ [0..(length pss - 1)]
  in  nub . filter (/= []) $ knock1Outss ++ knock2Outss

-- my turn to play, with the input provided. 
-- Do I win? 
playGameOfKyles :: CacheMap -> String -> (Bool, CacheMap)
playGameOfKyles cmap []   = (False, cmap)
playGameOfKyles cmap "I"  = (True,  cmap)
playGameOfKyles cmap "II" = (True,  cmap)
playGameOfKyles cmap ps = 
  let sps   = simplifyPins $ ps
      posss = compilePossibilities sps
      (tv, newmap)  = foldl' ( \ (tv, imap) istrs -> if tv == False then (tv, imap) else playGameOfKyles imap (compileMemoString istrs) )
                             (True, cmap) $ posss
      iwin = not tv
      result = if null sps then False else if iwin then True else False
      clookup = M.lookup ps cmap
  in  if clookup == Nothing
         then let finalmap = M.insert ps (iwin) newmap in (iwin, finalmap)
         else let Just ans = clookup in (ans, cmap)

runTestCases :: Int -> CacheMap -> IO ()
runTestCases 0 cmap = return ()
runTestCases n cmap = do
  npins <- getLine
  ps    <- getLine
  let (win, newmap) = playGameOfKyles cmap (compileMemoString . simplifyPins $ ps)
  putStrLn $ if win then "WIN" else "LOSE"
  runTestCases (n-1) newmap

main :: IO ()
main = do
  tcstr <- getLine
  let mymap = M.empty
  runTestCases (read tcstr) mymap

