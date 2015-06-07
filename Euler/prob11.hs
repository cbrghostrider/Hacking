-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

type Grid = [[Int]]

-- top left is 0, 0
type Coord = (Int, Int)

gSize :: Int
gSize = 20

chainLength :: Int
chainLength = 4

readGrid :: String -> Grid
readGrid = map (map read) . map words . lines 

fetchCell :: Grid -> Coord -> Int 
fetchCell gr co@(cx, cy) = (gr !! cy) !! cx

allCoords ::[Coord]
allCoords = [(x, y) | x<-[0..19], y<-[0..19] ]

-- converts a Coord into a list of 4 Coords
-- returns empty list if any component of list spills over beyond boundary
genTuples :: (Coord -> [Coord]) -> Coord -> [Coord]
genTuples tupFun co = let coords = filter (\ (cx', cy') -> cx' < gSize && cy' < gSize && cx' >=0 && cy' >=0) (take chainLength $ tupFun co) 
                      in  if length coords == chainLength then coords else []

--creates a chain of Coords
chain :: String -> Coord -> [Coord]
chain "l" co@(cx, cy)  = co : chain "l" (cx - 1, cy)
chain "r" co@(cx, cy)  = co : chain "r" (cx + 1, cy)
chain "u" co@(cx, cy)  = co : chain "u" (cx, cy - 1)
chain "d" co@(cx, cy)  = co : chain "d" (cx, cy + 1)
chain "ne" co@(cx, cy) = co : chain "ne" (cx + 1, cy - 1)
chain "nw" co@(cx, cy) = co : chain "nw" (cx - 1, cy - 1)
chain "se" co@(cx, cy) = co : chain "se" (cx + 1, cy + 1)
chain "sw" co@(cx, cy) = co : chain "sw" (cx - 1, cy + 1)

allTuplesForCoord :: Coord -> [[Coord]]
allTuplesForCoord co = map (\f -> genTuples f co) 
                            $ [chain "l", chain "r", chain "u", chain "d", chain "ne", chain "nw", chain "se", chain "sw"]

maxProd :: Grid -> Int
maxProd gr =  head . reverse . sort . map product . map (map (fetchCell gr)) . nub . concat . map allTuplesForCoord $ allCoords

main :: IO ()
main = do
  str <- readFile "/nfs/fm/disks/fm_dts_asvs05/ssjoshi/Programming/Haskell/Euler/prob11Grid.txt"
  let gr = readGrid str
  print gr
  putStrLn $ "The maximum product is: " ++ (show . maxProd $ gr)


