import Data.List

type Coord  = (Int, Int)        -- (row, col)
-- a layer is a ring of the matrix
type Layer  = (Coord, Int, Int) -- (top-left-crd, #rows, #cols)
type Matrix = [[Int]]

-- for a matrix ring with nc cols and nr rows, how many rotations is the identity rotation
simplifyRotation :: Int -> Int -> Int -> Int
simplifyRotation nr nc rot 
  | nr == 1 || nc == 1 = rot `mod` 2   --even number of rotations leave unchanged, odd numbers rotate by 1
  | otherwise          = let divideby = 2 * (nr - 2) + 2 * (nc - 2) + 4 in rot `mod` divideby

rotateSingleLine :: Matrix -> Layer -> Int -> Matrix
rotateSingleLine mat ly@(crd@(cr, cc), 1, 1  ) numrot = mat --nothing to rotate!
-- What does it even mean to rotate a matrix with only 1 row or only 1 column?
-- Currently leaving this as identity operation
rotateSingleLine mat ly@(crd@(cr, cc), 1, szc) numrot = mat
rotateSingleLine mat ly@(crd@(cr, cc), szr, 1) numrot = mat 

writeLayer :: Matrix -> Layer -> [Int] -> Matrix
writeLayer mat ly@(crd@(cr, cc), szr, szc) ns = 
  let newTopNums    = reverse . take szc                        $ ns
      newLeftNums   =           take (szr-2) . drop szc         $ ns
      newBotNums    =           take szc . drop (szr + szc - 2) $ ns
      newRightNums  = reverse . drop (szc + szr + szc - 2)      $ ns
      oldTopLine    = head . drop cr         $ mat
      oldBotLine    = head . drop (cr+szr-1) $ mat
      matTR         = (take cr mat)           ++ [(take cc oldTopLine) ++ (newTopNums)  ++ (drop (cc+szc) oldTopLine)] ++ (drop (cr+1) mat)
      matBR         = (take (cr+szr-1) matTR) ++ [(take cc oldBotLine) ++ (newBotNums)  ++ (drop (cc+szc) oldBotLine)] ++ (drop (cr+szr) matTR)
      matBR'        = transpose matBR
      oldLeftLine   = head . drop cc         $ matBR'
      oldRightLine  = head . drop (cc+szc-1) $ matBR'
      matLR         = (take cc matBR')        ++ [(take (cr+1) oldLeftLine) ++ (newLeftNums) ++ (drop (cr+szr-1) oldLeftLine)] ++ (drop (cc+1) matBR')
      matRR         = (take (cc+szc-1) matLR) ++ [(take (cr+1) oldRightLine) ++ (newRightNums) ++ (drop (cr+szr-1) oldRightLine)] ++ (drop (cc+szc) matLR)
      matout        = transpose matRR
  in  matout

readLayer :: Matrix -> Layer -> [Int]
readLayer mat ly@(crd@(cr, cc), szr, szc) = 
  let lineTop   = reverse . take szc       . drop cc       . head . drop cr                     $ mat
      lineBot   =           take szc       . drop cc       . head . drop (cr+szr-1)             $ mat
      lineLeft  =           take (szr - 2) . drop (cr + 1) . head . drop cc .         transpose $ mat
      lineRight = reverse . take (szr - 2) . drop (cr + 1) . head . drop (cc+szc-1) . transpose $ mat
  in  lineTop ++ lineLeft ++ lineBot ++ lineRight

rotateFatLayer :: Matrix -> Layer -> Int -> Matrix
rotateFatLayer mat ly@(crd@(cr, cc), szr, szc) numrot = 
  let ns = reverse $ readLayer mat ly
      rs = (drop numrot ns) ++ (take numrot ns)
  in  writeLayer mat ly (reverse rs)

rotateLayer :: Matrix -> Int -> Layer -> Matrix
rotateLayer mat numrot ly@(crd@(cr, cc), szr, szc) 
  | szr == 1 || szc == 1 = rotateSingleLine mat ly (simplifyRotation szr szc numrot) 
  | otherwise            = rotateFatLayer   mat ly (simplifyRotation szr szc numrot)

rotateMatrix :: Matrix -> Int -> Matrix
rotateMatrix mat numrot = 
  let midr     = (length mat `div` 2)            + (length mat `mod` 2) 
      midc     = ((length . head $ mat) `div` 2) + ((length . head $ mat) `mod` 2)
      startlyr = ((0, 0), length mat, (length . head) mat)
      layers   = take (min midr midc) $ unfoldr (\ ly@((tlr, tlc), szr, szc) -> Just (ly, ((tlr+1, tlc+1), szr-2, szc-2)) ) startlyr
      matout   = foldl' (\accmat lyr -> rotateLayer accmat numrot lyr) (mat) $ layers 
  in  matout

displayMatrix :: Matrix -> String
displayMatrix = unlines . map (unwords . map show)

main :: IO ()
main = do
  ip <- getContents
  let [m, n, r] = map read . words . head . lines $ ip
      matrix    = map (map read . words) . tail . lines $ ip
      rotated   = rotateMatrix matrix r
  putStrLn $ displayMatrix rotated
