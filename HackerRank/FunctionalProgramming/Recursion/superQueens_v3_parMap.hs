import Data.List
import Control.Parallel
import Control.Parallel.Strategies

type Board = [[Char]]
type Coord = (Int, Int) -- (row, col)

unsafe :: Char
unsafe = 'U'

onBoardCell :: Board -> Coord -> Bool
onBoardCell bd crd@(cr, cc) = (cr >= 0) && (cc >= 0) && (cr < bsize) && (cc < bsize)
  where bsize = length bd

readCell :: Board -> Coord -> Char
readCell board (r, c) = (board !! r) !! c

markCell :: Board -> Coord -> Char -> Board
markCell inBoard crd@(cr, cc) ch = 
  let prevLines = take cr inBoard
      thisLine  = head . drop cr $ inBoard
      nextLines = drop (cr+1) inBoard
  in  prevLines ++ [(take cc thisLine) ++ [ch] ++ (drop (cc+1) thisLine)] ++ nextLines

markKnightPathUnsafe :: Board -> Coord -> Board
markKnightPathUnsafe inBd crd@(cr, cc) = 
  let knightcrds = [(cr-1, cc+2), (cr+1, cc+2), (cr-1, cc-2), (cr+1, cc-2), 
                    (cr+2, cc-1), (cr+2, cc+1), (cr-2, cc-1), (cr-2, cc+1)]
      candCs     = filter (onBoardCell inBd) knightcrds
      outBd      = foldl' (\bd cell -> markCell bd cell unsafe) (inBd) $ candCs
  in  outBd

markDiagonalsUnsafe :: Board -> Coord -> Board
markDiagonalsUnsafe inBd crd@(cr, cc) = 
  let q1crds = scanl (\acc f -> f acc) (cr, cc) . take (length inBd - 1) . repeat $ (\(r, c) -> (r-1, c+1))
      q2crds = scanl (\acc f -> f acc) (cr, cc) . take (length inBd - 1) . repeat $ (\(r, c) -> (r-1, c-1))
      q3crds = scanl (\acc f -> f acc) (cr, cc) . take (length inBd - 1) . repeat $ (\(r, c) -> (r+1, c+1))
      q4crds = scanl (\acc f -> f acc) (cr, cc) . take (length inBd - 1) . repeat $ (\(r, c) -> (r+1, c-1))
      candCs = filter (onBoardCell inBd) $ q1crds ++ q2crds ++ q3crds ++ q4crds
      outBd  = foldl' (\bd cell -> markCell bd cell unsafe) (inBd) $ candCs
  in  outBd

markRowUnsafe :: Board -> Int -> Board
markRowUnsafe bd n = (take n bd) ++ [take (length bd) $ repeat unsafe] ++ (drop (n+1) bd)

markColUnsafe :: Board -> Int -> Board
markColUnsafe bd n = transpose . (\b -> markRowUnsafe b n) . transpose $ bd

-- given this board, and a position that queen was placed, mark attacked cells invalid
-- also marks this and possibly prior queens positions as unsafe, which is ok!
markBoardCellsUnsafe :: Board -> Coord -> Board
markBoardCellsUnsafe inBd crd@(cr, cc) = 
  let rbd = markRowUnsafe        inBd cr
      cbd = markColUnsafe        rbd  cc
      dbd = markDiagonalsUnsafe  cbd crd
      kbd = markKnightPathUnsafe dbd crd
  in  kbd

-- number of ways to finish puzzle, by placing this queen on this row
placeQueenOnRow :: Board -> Int -> Int
placeQueenOnRow inBoard rowNum = 
  let bsize     = length inBoard
      candCells = filter ((/= unsafe) . (readCell inBoard)) $ [(rowNum, c) | c <- [0..(bsize-1)]]
      recWays   = parMap rdeepseq (\cell -> placeQueenOnRow (markBoardCellsUnsafe inBoard cell) (rowNum + 1)) $ candCells
      numWays   = if rowNum == (bsize - 1) then length candCells else sum recWays
  in  numWays

createInitBoard :: Int -> Board
createInitBoard n = [[ ' ' | c <- [1..n]] | r <- [1..n]]

solveProblem :: Int -> Int 
solveProblem n = placeQueenOnRow (createInitBoard n) 0

main :: IO ()
main = do
  nstr <- getLine
  putStrLn $ show . solveProblem . read $ nstr
