-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Text.Printf
import Data.List
import Data.Ord

type Coord = (Int, Int)

findBottomRCornerPt :: [Coord] -> Coord
findBottomRCornerPt = foldl1' (\accpt pt -> if snd pt < snd accpt then pt else if snd pt > snd accpt then accpt else if fst pt > fst accpt then pt else accpt)

-- takes two vectors and finds the angle between them
angleBetween :: Coord -> Coord -> Double
angleBetween v1@(x1, y1) v2@(x2, y2) = 
  let v1mag = sqrt . fromIntegral $ (x1*x1 + y1*y1) 
      v2mag = sqrt . fromIntegral $ (x2*x2 + y2*y2)
      uv1   = ((fromIntegral x1) / v1mag, (fromIntegral y1) / v1mag)
      uv2   = ((fromIntegral x2) / v2mag, (fromIntegral y2) / v2mag)
      uvdotprod = (fst uv1 * fst uv2) + (snd uv1 * snd uv2)
      angle = acos uvdotprod
  in  if (x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0)then 0.0 else if uv1 == uv2 then 0.0 else angle

computeAngleWith :: Coord -> Coord -> Double
computeAngleWith lowPt myPt = angleBetween (fst myPt - fst lowPt, snd myPt - snd lowPt) unitxv
  where unitxv = (1, 0)

counterClockWise :: Coord -> Coord -> Coord -> Bool
counterClockWise p1@(p1x, p1y) p2@(p2x, p2y) p3@(p3x, p3y) = ((p2x - p1x) * (p3y - p1y) - (p2y - p1y) * (p3x - p1x)) > 0

-- takes a list of Coords sorted by their polar angle with bottom corner pt (which is head)
-- returns a list of Coords on the convex hull perimeter
grahamScan :: [Coord] -> [Coord] -> [Coord]
grahamScan accpts []  = accpts
grahamScan accpts pts = 
  let initpt  = head . tail $ accpts
      nextpt  = head accpts
      thispt  = head pts
      retval  =   if counterClockWise initpt nextpt thispt
                     then grahamScan (thispt : accpts) (tail pts)
                     else if length accpts == 2 
                             then grahamScan (accpts) (tail pts)
                             else grahamScan (tail accpts) pts 
  in  retval

perimeter :: [Coord] -> Double
perimeter prms = distFinal + (fst $ foldl' (\acc@(rv, lpt) npt -> (rv + distance lpt npt, npt)) (0.0, head prms) (tail prms))
  where
    distFinal = distance (head prms) (last prms)
    distance p1@(p1x, p1y) p2@(p2x, p2y) = let xdelta = p1x - p2x 
                                               ydelta = p1y - p2y 
                                           in  sqrt . fromIntegral $ (xdelta * xdelta + ydelta * ydelta)

solve :: [Coord] -> Double
solve points = 
  let pts    = nub points
      ptBR   = findBottomRCornerPt pts
      ptRest = sortBy (comparing (computeAngleWith ptBR)) $ pts \\ [ptBR]
      prm    = grahamScan ((head ptRest) : [ptBR]) ((tail ptRest) )
  in  perimeter prm

main :: IO ()
main = do
  n <- readLn :: IO Int
  content <- getContents
  let  
    points = map (\[x, y] -> (x, y)). map (map (read::String->Int)). map words. lines $ content
    ans = solve points
  printf "%.1f\n" ans


