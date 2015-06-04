import Data.List
import Data.Ord
import Data.Maybe 

type Coord    = (Int, Int)   -- the coordinates in the crossword puzzle (row, col)
type PosValue = (Int, Char)  -- at this position from start, with this value
type Sequence = ([(PosValue)]) -- Another way to represent a word
data Direction= Vertical | Horizontal deriving (Show, Eq, Ord)

c_NUMROWS :: Int
c_NUMROWS = 10

c_NUMCOLS :: Int
c_NUMCOLS = c_NUMROWS 

allCoords :: [Coord]
allCoords = [(r, c) | r <- [0..(c_NUMROWS-1)], c <- [0..(c_NUMCOLS-1)]]

isUnfulfilled :: Sequence -> Bool
isUnfulfilled []       = False
isUnfulfilled (pv:pvs) = if snd pv == '-' then True else isUnfulfilled pvs

getUnfulfilledSeq :: [Sequence] -> Sequence
getUnfulfilledSeq []     = []
getUnfulfilledSeq (s:ss) = if isUnfulfilled s then s else getUnfulfilledSeq ss  

splitOn :: (Char -> Bool) -> String -> [String]
splitOn _ [] = []
splitOn f ss = if (f . head $ ss) then []:recurse else firstWord : restWords
  where
    recurse   = splitOn f (tail ss)
    firstWord = if null recurse then [head ss] else (head ss : head recurse)
    restWords = if null recurse then [] else tail recurse

-- not checked!
letterAt :: [String] -> Coord -> Char
letterAt cws crd@(cr, cc) = ((cws !! cr) !! cc)

processDictionary :: String -> [String]
processDictionary = splitOn (== ';')

satisfiesConstraint :: Sequence -> String -> Bool
satisfiesConstraint pvs ss = if null pvs' then True else ((== (sortBy (comparing fst) pvs')) . sortBy (comparing fst) . filter (`elem` pvs') $ zip [0..] ss)
  where pvs' = filter ((/= '-') . snd ) pvs

-- given a dictionary, a length to fill, and a positional encoding, 
-- find a list of candidates from the dictionary
findCandidateWords :: [String] -> Sequence -> [String]
findCandidateWords dict pvs = filter (satisfiesConstraint pvs) . filter ((== len) . length) $ dict
  where len = length pvs

-- at current cell, if there is a seq STARTING here and going rightwards, get all those cells
-- this will return all letters AND '-' signs in the sequence
getRightwardSeq :: Int -> [String] -> Coord -> Sequence
getRightwardSeq ind cws crd@(cr, cc) = 
  if (cc >= c_NUMCOLS) || (cr >= c_NUMROWS) || ((cws `letterAt` crd) == '+') 
      then [] else (ind, (cws `letterAt` crd)) : (getRightwardSeq (ind+1) cws (cr, cc+1))

getDownwardSeq :: Int -> [String] -> Coord -> Sequence
getDownwardSeq ind cws crd@(cr, cc) = 
  if (cc >= c_NUMCOLS) || (cr >= c_NUMROWS) || ((cws `letterAt` crd) == '+') 
      then [] else (ind, (cws `letterAt` crd)) : (getDownwardSeq (ind+1) cws (cr+1, cc))

rightwardPossible :: [String] -> Coord -> Bool
rightwardPossible cws crd@(cr, cc) = ((cc == 0) || ((cws `letterAt` (cr, cc - 1)) == '+')) && ((cws `letterAt` crd) /= '+') 
                                       && (((cc + 1) /= c_NUMCOLS) && ((cws `letterAt` (cr, cc + 1)) /= '+'))

downwardPossible :: [String] -> Coord -> Bool
downwardPossible cws crd@(cr, cc)  = ((cr == 0) || ((cws `letterAt` (cr - 1, cc)) == '+')) && ((cws `letterAt` crd) /= '+')
                                       && (((cr + 1) /= c_NUMROWS) && ((cws `letterAt` (cr + 1, cc)) /= '+'))

placeWord :: Direction -> [String] -> Coord -> String -> [String]
placeWord _          cws crd@(cr, cc) []      = cws
placeWord Horizontal cws crd@(cr, cc) placeMe = 
  let line    = (head . drop cr $ cws)
      newline = (take cc line) ++ placeMe ++ (drop (cc + (length placeMe)) line)
  in  (take cr cws) ++ [newline] ++ (drop (cr + 1) cws)
placeWord Vertical cws crd@(cr, cc) (letter : restPlaceMe) = 
  let line    = (head . drop cr $ cws)
      newline = (take cc line) ++ [letter] ++ (drop (cc + 1) line)
  in  placeWord Vertical ((take cr cws) ++ [newline] ++ (drop (cr+1) cws)) (cr+1, cc) restPlaceMe
  

tryPlacements :: [String] -> [String] -> Coord -> (Sequence, Sequence) -> (Bool, [String])
tryPlacements dict cws crd@(cr, cc) (chosenH, chosenV) =
  let horizCands = zip (repeat Horizontal) $ findCandidateWords dict chosenH
      vertCands  = zip (repeat Vertical)   $ findCandidateWords dict chosenV
      resolutions= map (\ (dir, word) -> solveCrossword (dict \\ [word]) (placeWord dir cws crd word)) $ horizCands ++ vertCands
      filtRess   = filter ((==True) . fst) $ resolutions
  in  if null filtRess then (False, cws) else (True, (snd . head $ filtRess))


-- return value is (is-possible, new-crossword)
solveCrossword :: [String] -> [String] -> (Bool, [String])
solveCrossword dict cws = 
  let candCrds = filter (\c -> rightwardPossible cws c || downwardPossible cws c) $ allCoords
      crdsSeqs = zip candCrds . map (\c -> (getRightwardSeq 0 cws c) : [(getDownwardSeq 0 cws c)]) $ candCrds
      possCSs  = filter ( \ (_, seqs) -> (not . null . getUnfulfilledSeq $ seqs)) $ crdsSeqs
      (chosencrd, chosens)  = head  possCSs
      (chosenH, chosenV)    = (head chosens, last chosens)
  in  if null candCrds || null possCSs then (True, cws) else tryPlacements dict cws chosencrd (chosenH, chosenV) 

main ::IO ()
main = do 
  ip <- getContents
  let cws  = take c_NUMROWS . lines $ ip
  let dict = processDictionary . head . drop c_NUMROWS . lines $ ip
  let (poss, solvedcws) = solveCrossword dict cws
  putStrLn $ unlines (if poss then solvedcws else ["Crossword unsolvable!"] ++ solvedcws)
