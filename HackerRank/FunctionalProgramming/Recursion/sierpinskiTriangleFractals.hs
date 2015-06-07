-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

type Coord    = (Int, Int)            -- (Row, Col), top left is (0, 0)
type Triangle = (Coord, Coord, Coord) -- (top, bot-left, bot-right)

numRows :: Int
numRows = 32

numCols :: Int
numCols = 63

lineToChars :: [Int] -> String
lineToChars os = map (\n -> if n`elem` os then '1' else '_') $ [1..numCols]

genIteration0 :: ([String], [Triangle])
genIteration0 = 
  let ss = take numRows . map lineToChars . ([[numRows]] ++ ) $ unfoldr (\rs -> let nrs = ((head rs - 1) : rs) ++ [last rs + 1] in Just (nrs, nrs)) [numRows]
      ts = [((0, numRows-1), (numRows-1, 0), (numRows-1, numCols-1))]
  in  (ss, ts)

-- takes a triangle to further fractalize, and returns
-- (triangle-to-be-nullified, [new-triangles-in-fractal])
createNewTriangles :: Triangle -> (Triangle, [Triangle])
createNewTriangles ts@(top, botl, botr) = 
  let szc      = ((snd botl + snd botr) `div` 2)  + ((snd botl + snd botr) `mod` 2)
      szcby14  = ((snd botl + szc - 1) `div` 2)  + ((snd botl + szc - 1) `mod` 2) 
      szcby34  = ((snd botr + szc + 1) `div` 2)  + ((snd botr + szc + 1) `mod` 2) 
      szr      = ((fst top + fst botl) `div` 2) -- + ((fst top + fst botl) `mod` 2)  
      midbot   = ((fst botl), szc)
      midbotm1 = ((fst botl), (szc - 1))
      midbotp1 = ((fst botl), (szc + 1))
      midl     = (szr+1, szcby14)
      midlp1   = (szr+1, szcby14 + 1)
      midlup   = (szr,   szcby14 + 1)
      midr     = (szr+1, szcby34)
      midrm1   = (szr+1, szcby34 - 1)
      midrup   = (szr,   szcby34 - 1)
  in  ((midlp1, midrm1, midbot), [(top, midlup, midrup), (midl, botl, midbotm1), (midr, midbotp1, botr)])

nullifyRow :: [String] -> (Coord, Coord) -> [String]
nullifyRow ss (left@(lr, lc), right@(rr, rc)) = priorRows ++ [thisRow] ++ restRows
  where
    priorRows = take (lr) ss
    restRows  = drop (lr+1) ss
    myRow     = last . take (lr+1) $ ss
    thisRow   = ((take (lc) myRow) ++ (take (rc - lc + 1) (repeat '_')) ++ (drop (rc+1) myRow) )

-- sets all the locations within this triangle to '_'
nullifyTriangle :: Triangle -> [String] -> [String]
nullifyTriangle tri@(tl, tr, bot) ss = foldl' (nullifyRow) ss $ rowCoords 
  where 
    rowCoords = take (fst bot - fst tl + 1) $ ((tl, tr) : (unfoldr (\ (l@(lr, lc), r@(rr, rc)) -> let nc = ((lr+1, lc+1), (rr+1, rc-1)) in Just (nc, nc)) $ (tl, tr)))

-- runs one more iteration of fractalization
iterateTri :: ([String], [Triangle]) -> ([String], [Triangle])
iterateTri (ss, ts) = foldl' (\acc@(ass, ats) t -> 
                                 let (nt, newts) = createNewTriangles t
                                     newss = nullifyTriangle nt ass
                                 in  (newss, ats ++ newts)
                             ) 
                             (ss, []) $ ts

fractalize :: Int -> Int -> ([String], [Triangle]) -> ([String], [Triangle])
fractalize 0    times _        = 
  let initseq = genIteration0 
  in  if times == 1 then initseq else fractalize 1 times initseq

fractalize inum times (ss, ts) = 
  let newseq = iterateTri (ss, ts)
  in  if inum == times - 1 then newseq else fractalize (inum+1) times newseq

main :: IO ()
main = do
  nstr <- getLine 
  let css = fst $ fractalize 0 (1 + read nstr) ([], []) 
  putStrLn $ unlines css

