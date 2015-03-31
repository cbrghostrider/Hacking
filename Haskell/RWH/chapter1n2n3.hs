import Data.List
import Data.Ord

main1 = interact charCount
  where lineCount xs = (show . length . concat . map words . lines $ xs) ++ "\n"
        wordCount xs = (show . length . concat . map words . lines $ xs) ++ "\n"
        charCount xs = (show . sum . map length . concat . map words . lines $ xs) ++ "\n"

lastButOne :: [a] -> a
lastButOne []     = error "Empty list"
lastButOne [a]    = error "Not enough elements in list"
lastButOne [a, b] = a
lastButOne (x:xs) = lastButOne xs

data MyList a = Cons a (MyList a)
              | Nil 
              deriving (Show)


fromList :: [a] -> MyList a
fromList [] = Nil
fromList (x:xs) = Cons x (fromList xs)

toList :: MyList a -> [a]
toList Nil = []
toList (Cons x rl) = x : toList rl


-- chapter 3 end of chapter stuff

numElems :: [a] -> Int
numElems [] = 0
numElems (x:xs) = 1 + numElems xs


lmean :: [Int] -> Maybe Double
lmean [] = Nothing
lmean ls = Just $ (fromIntegral.fst $ans) / (fromIntegral.snd $ans)
  where ans = foldr (\num (rs, rn) -> (rs + num, rn + 1)) (0, 0) ls

makePalin :: [a] -> [a]
makePalin ls = ls ++ (reverse ls) 

makePalin' :: [a] -> [a]
makePalin' [] = []
makePalin' (x:xs) = (x : (makePalin' xs)) ++ [x]

isPalin :: Eq a => [a] -> Bool
isPalin xs = xs == reverse xs

sortOnLength :: [[a]] -> [[a]]
sortOnLength = sortBy (comparing length)

intersperse' :: a -> [[a]] -> [a]
intersperse' _ [] = []
intersperse' elem ls = init . concat . map (++ [elem]) $ ls

data TreeType a = Node a (TreeType a) (TreeType a) | Empty

heightMyTree :: TreeType a -> Int
heightMyTree Empty = 0
heightMyTree (Node _ lt rt) = 
  let lth = heightMyTree lt
      rth = heightMyTree rt
  in  if lth < rth then 1 + rth else 1 + lth

data Direction = Left | Right | Straight
type Coord = (Int, Int)

getDirection :: Coord -> Coord -> Coord -> Direction
getDirection p1@(p1x, p1y) p2@(p2x, p2y) p3@(p3x, p3y) = 



