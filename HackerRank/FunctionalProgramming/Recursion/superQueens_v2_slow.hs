-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

type Coord = (Int, Int) -- (row, col)
type Board = [Coord]    -- will store a list of unsafe coordinates

onBoardCell :: Int -> Coord -> Bool
onBoardCell bsize crd@(cr, cc) = (cr >= 0) && (cc >= 0) && (cr < bsize) && (cc < bsize)

markKnightPathUnsafe :: Int -> Coord -> Board
markKnightPathUnsafe bsize crd@(cr, cc) = 
  let knightcrds = [(cr-1, cc+2), (cr+1, cc+2), (cr-1, cc-2), (cr+1, cc-2), 
                    (cr+2, cc-1), (cr+2, cc+1), (cr-2, cc-1), (cr-2, cc+1)]
  in  filter (onBoardCell bsize) knightcrds

markDiagonalsUnsafe :: Int -> Coord -> Board
markDiagonalsUnsafe bsize crd@(cr, cc) = 
  let q1crds = filter (onBoardCell bsize) . scanl (\acc f -> f acc) (cr, cc) . take (bsize - 1) . repeat $ (\(r, c) -> (r-1, c+1))
      q2crds = filter (onBoardCell bsize) . scanl (\acc f -> f acc) (cr, cc) . take (bsize - 1) . repeat $ (\(r, c) -> (r-1, c-1))
      q3crds = filter (onBoardCell bsize) . scanl (\acc f -> f acc) (cr, cc) . take (bsize - 1) . repeat $ (\(r, c) -> (r+1, c+1))
      q4crds = filter (onBoardCell bsize) . scanl (\acc f -> f acc) (cr, cc) . take (bsize - 1) . repeat $ (\(r, c) -> (r+1, c-1))
  in  q1crds ++ q2crds ++ q3crds ++ q4crds

markRowUnsafe :: Int -> Int -> Board
markRowUnsafe bsize n = [(n, c) | c <- [0..(bsize-1)]]

markColUnsafe :: Int -> Int -> Board
markColUnsafe bsize n = [(r, n) | r <- [0..(bsize-1)]] 

-- given this board, and a position that queen was placed, mark attacked cells invalid
-- also marks this and possibly prior queens positions as unsafe, which is ok!
markBoardCellsUnsafe :: Int -> Board -> Coord -> Board
markBoardCellsUnsafe bsize inBd crd@(cr, cc) = 
  let rbd = markRowUnsafe        bsize cr
      cbd = markColUnsafe        bsize cc
      dbd = markDiagonalsUnsafe  bsize crd
      kbd = markKnightPathUnsafe bsize crd
  in  nub $ inBd ++ rbd ++ cbd ++ dbd ++ kbd

-- number of ways to finish puzzle, by placing this queen on this row
placeQueenOnRow :: Int -> Board -> Int -> Int
placeQueenOnRow bsize inBoard rowNum = 
  let candCells = filter (not . (`elem` inBoard))  $ [(rowNum, c) | c <- [0..(bsize-1)]]
      recWays   = map (\cell -> placeQueenOnRow bsize (markBoardCellsUnsafe bsize inBoard cell) (rowNum + 1)) $ candCells
      numWays   = if rowNum == (bsize - 1) then length candCells else sum recWays
  in  numWays

solveProblem :: Int -> Int 
solveProblem n = placeQueenOnRow n [] 0

main :: IO ()
main = do
  nstr <- getLine
  putStrLn $ show . solveProblem . read $ nstr

