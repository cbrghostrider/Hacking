-- Most of Problems 1 to 43

import Misc
import Data.List
import Data.Char
import Data.Function 
import Data.Ord
import Data.Tuple
import Data.Ratio
import Control.Monad
import Numeric

-- Project Euler: Problem 1
mult35 = sum [x | x <- [1..999], (x `mod` 3 == 0) || (x `mod`5 == 0)]

-- Project Euler: Problem 2
--fibs = 1: 2 : zipWith (+) fibs (tail fibs)
--ans2 = sum . filter (\x -> x `mod` 2 == 0) . (takeWhile (<=4000000)) $ fibs

-- Project Euler: Problem 3
ans3 :: Integer -> Integer
ans3 val = head . filter isPrime . filter (\x -> val `mod` x == 0) . reverse $ [1..newVal] 
  where newVal = (1 + (val `div` 2)) :: Integer

-- Project Euler: Problem 4
ans4 :: Integer
ans4 = head . dropWhile (not.isPalindrome.show) . reverse . sort $ [x * y | x <- listNums, y <- listNums]
  where listNums = [999, 998..100]

-- Project Euler: Problem 5
ans5 :: Integer
ans5 = head. dropWhile (\n -> not . and . map (\x -> (n `mod` x == 0)) $ [20, 19..1]) $ [21..]

-- Project Euler: Problem 6
ans6 :: Integer -> Integer
ans6 n = ((^2).sum $ listNums) - (sum. map (^2) $ listNums)
  where listNums = [1..n]

-- Project Euler: Problem 7
ans7 :: Integer -> Integer
ans7 n = head . reverse . take (fromIntegral n) $ primeNumbers 

-- Project Euler: Problem 8
ans8 :: String -> Integer
ans8 str = head . reverse . sort . take (length nums - 4) $ zipWith5 (\ a b c d e -> a * b * c * d * e) nums numsL1 numsL2 numsL3 numsL4  
  where
    rotateLeft ns =tail ns ++ [head ns]
    nums   = (map (read . return) str) :: [Integer]
    numsL1 = rotateLeft nums
    numsL2 = rotateLeft numsL1
    numsL3 = rotateLeft numsL2
    numsL4 = rotateLeft numsL3

main8 :: IO ()
main8 = do 
  num <- getLine
  putStrLn ("Answer is: " ++ (show . ans8 $ num))


-- Project Euler: Problem 9
ans9 :: Int
ans9 = (\(x, y, z) -> x*y*z) . head . filter (\ (a, b, c) -> a < b && b < c && a^2 + b^2 == c^2 && a + b + c == 1000) 
           $ [(a, b, c) | c <- [1..1000], b <- [1..c], a <- [1..b]]

-- Project Euler: Problem 10
ans10 :: Integer
ans10 = sum.primesUpTo $ 2000000

-- Project Euler: Problem 11
-- solution in prob11.hs

-- Project Euler: Problem 12
ans12 :: Integer
ans12 = fst. head . dropWhile (\(t, l) -> l <=500 ). zip triNums . map length . map factors $ triNums

-- Project Euler: Problem 13

chrToInt :: Char -> Int
chrToInt x = ord x - ord '0'

transpose' :: [[a]] -> [[a]]
transpose' xss 
  | ( and . map null $ xss ) == True = []
  | otherwise = (map head $ xss) : (transpose' . map tail $ xss)

collapseMatrix :: [[Int]] -> [Int]
collapseMatrix xss = (map chrToInt . show $ fcarry) ++ fpss
  where
    (fcarry, fpss) = foldl foldFunc (0, []) (reverse . map sum . transpose' $ xss)
    foldFunc = (\ (carry, ns) x -> ((x + carry) `div` 10, ((x + carry) `mod` 10) : ns)) 

main13 :: IO ()
main13 = interact $ concat . map show . collapseMatrix . map (map chrToInt) . lines 

-- Project Euler: Problem 14
collatz :: Integer -> [Integer]
collatz n
  | n == 1         = []
  | n `mod` 2 == 0 = n2 : collatz n2
  | otherwise      = n3 : collatz n3
    where
      n2 = n `div` 2
      n3 = 3*n + 1

ans14 :: Integer 
ans14 = fst . head . reverse . sortBy (compare `on` snd) . zip nums . map length . map collatz $ nums
  where nums = [1..999999]


-- Project Euler: Prob 14- dyn programming
collatzLen :: Integer -> Integer
collatzLen upTo =  fst . head . reverse . sortBy (compare `on` snd) . tail . zip [0..] . take (fromIntegral upTo) $ collatzMemo 
  where
    collatzLen' n 
      | n == 0          = 0 -- won't be reached
      | n == 1          = 0
      | n `mod` 2 == 0  = 1 + (collatzMemo !! (n `div` 2))
      | otherwise       = 1 + (collatzMemo !! (3*n + 1))
    collatzMemo = map collatzLen' [0..]

ans14' :: Integer
ans14' = collatzLen 999999

problem14 = snd $ maximumBy (comparing fst) $ map ((\x->(length x, head x)).collatsChain) [1..999999]
        where
        collatsChain = unfoldr ff
        ff 1 = Nothing
        ff n | n `mod` 2 == 0 = Just (n, n `div` 2)
             | otherwise = Just (n, 3*n+1)

-- Project Euler: Problem 15
data Movement = Dwn | Rght deriving (Eq, Ord, Show)
moveOnce xs = [Dwn:xs , Rght:xs]
ans15 gsize = length . filter (== ((take gsize (repeat Dwn)) ++ (take gsize (repeat Rght)))) . map sort . paths $ gsize
paths gsize = foldl (>>=) (return [])  . take (gsize * 2) . repeat $ moveOnce 

facts :: [Integer]
facts = scanl1 (*) [1..]

ans15' :: Int -> Int
ans15' gsize = length $ combiner (take gsize . repeat $ Dwn) (take gsize . repeat $ Rght)

combiner :: [Movement] -> [Movement] -> [[Movement]]
combiner xs [] = [xs]
combiner [] ys = [ys]
combiner (x:xs) (y:ys) = (map (x:) $ combiner xs (y:ys)) ++ (map (y:) $ combiner (x:xs) ys)

-- Project Euler: Problem 16 
ans16Cheat = sum . map chrToInt . show $ (2 ^ 1000) 

-- Project Euler: Problem 17
-- answer is in prob17.hs

-- Project Euler: Problem 18
{-
data Tree a = EmptyTree | Node a (Tree a) (Tree a) deriving (Show)

readTree :: [[a]] -> Tree a
readTree = head. head . scanr readRow (repeat EmptyTree)

readRow ::[a] -> [Tree a] -> [Tree a]
readRow row lowerLvl = foldr (\(n, val) partTreeRow -> (Node val (lowerLvl !! n) (lowerLvl !! (n+1))) : partTreeRow) [] (zip [0..] row)

readNode :: (Num a) => Tree a -> a
readNode EmptyTree = 0
readNode (Node x _ _ ) = x

transformTree :: (Num a, Ord a) => (a -> a -> a) -> Tree a -> Tree a
transformTree fn EmptyTree = EmptyTree
transformTree fn (Node a l r) = 
  let leftPathVal  = fn a $ readNode ltr
      rightPathVal = fn a $ readNode rtr
      ltr = transformTree fn l
      rtr = transformTree fn r
  in  if leftPathVal < rightPathVal then Node rightPathVal ltr rtr else Node leftPathVal ltr rtr
collapseTree :: (Num a, Ord a) => (a -> a -> a) -> Tree a -> a
collapseTree fn EmptyTree = 0
collapseTree fn (Node a left right) = 
  let leftPathVal  = fn a $ collapseTree fn left
      rightPathVal = fn a $ collapseTree fn right
  in  if leftPathVal < rightPathVal then rightPathVal else leftPathVal
  -}  
processAll :: (Num a, Ord a) => [[a]] -> a
processAll = head. head . scanr processRow (repeat 0)

processRow :: (Num a, Ord a) => [a] -> [a] -> [a]
processRow row lowerLvl = foldr (\(n, val) partRow -> (maxChoice val (lowerLvl !! n) (lowerLvl !! (n+1))) : partRow) [] (zip [0..] row)
  where
    maxChoice v l r = if (v + l) < (v + r) then (v + r) else (v + l)

main18 :: IO ()
main18 = interact $ show . processAll . map (map read) . map words . lines 

-- Project Euler: Problem 19
data WeekDay = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday deriving (Show, Read, Eq, Ord, Enum)
data Months = Jan | Feb | Mar | Apr | May | Jun | Jul | Aug | Sep | Oct | Nov | Dec deriving (Show, Read, Eq, Ord, Enum)
type Year = Int
type Date = (Months, Year)

weekday :: Int -> WeekDay
weekday 0 = Monday
weekday n = succ . weekday $ n - 1

nextMonth :: Date -> Date
nextMonth (Dec, y) = (Jan, y+1)
nextMonth (m, y)   = (succ m, y)

daysForMonth :: Date -> Int
daysForMonth (m, y) 
  | m == Sep || m == Apr || m == Jun || m == Nov = 30
  | m == Jan || m == Mar || m == May || m == Jul || m == Aug || m == Oct || m == Dec = 31
  | m == Feb = if (y `mod` 4 == 0 && y `mod` 100 /= 0) || (y `mod` 400) == 0 then 29 else 28

-- cumulative days until first of successive new months
cumuDaysForMonths :: [Int]
cumuDaysForMonths = scanl1 (+) . map daysForMonth . takeWhile (\(_, y) -> y <= 2000) . scanl (\d f -> f d) (Jan, 1900) $ repeat nextMonth

-- which weekday was 1st of each successive month
weekdayForMonths :: [WeekDay]
weekdayForMonths = map weekday . map (`mod` 7) $ cumuDaysForMonths

main19 = length . filter (== Sunday) . drop 12 $ weekdayForMonths 

-- Project Euler: Problem 20
ans20 :: Int
ans20 = sum . map chrToInt . show . foldr1 (*) $ [1..100]

-- Project Euler: Problem 21
divSumPairs :: [(Integer, Integer)]
divSumPairs = filter (\(x, y) -> x /= y) . map (\(x, ls) -> (x, sum ls)) . map (\(x, ls) -> (x, (/= x) `filter` ls)) . zip nums . map factors $ nums
  where nums = [1..9999]

ans21 :: Integer
ans21 = (`div` 2). sum . concat . map (\(x, y) -> [x, y]) . intersect divSumPairs . map swap $ divSumPairs

-- Project Euler: Problem 22
ans22 :: [String] -> Integer
ans22 ns = sum . map (\ (i, iname) -> (i * (sum . map letToInt $ iname))). zip [1..] .sort $ ns
  where letToInt x = fromIntegral $ ord x - ord 'A' + 1

main22 = interact $  show . ans22 . words . map (\x->if x == ',' then ' ' else x) . filter (/= '\"')

-- Project Euler: Problem 23
abundantNums :: [Integer]
abundantNums = map fst . filter (\(x, s) -> s > x) . map (\(x, ls) -> (x, sum ls)) . map (\(x, ls) -> (x, (/=x) `filter` ls)) . zip nums . map factors $ nums
  where nums = [1..28123]

isSumOfAbundantNums :: Integer -> Bool
isSumOfAbundantNums n = (/= 0) . length . filter (`elem` abundantNums) . filter (> 0) . map (n-) $ abundantNums

ans23 :: Integer
ans23 = sum . filter (not.isSumOfAbundantNums) $ nums 
  where nums = [1..28123]

-- Project Euler: Problem 24
ans24 :: Integer
ans24 = [ten*(10^9) + nine*(10^8) + eight*(10^7) + seven*(10^6) + six*(10^5) + five*(10^4) + four*(10^3) + three*(10^2) + two*(10^1) + one*(1)
                 | ten   <- all,
                   nine  <- all \\ [ten],
                   eight <- all \\ [nine, ten],
                   seven <- all \\ [eight, nine, ten],
                   six   <- all \\ [seven, eight, nine, ten],
                   five  <- all \\ [six, seven, eight, nine, ten],
                   four  <- all \\ [five, six, seven, eight, nine, ten],
                   three <- all \\ [four, five, six, seven, eight, nine, ten],
                   two   <- all \\ [three, four, five, six, seven, eight, nine, ten],
                   one   <- all \\ [two, three, four, five, six, seven, eight, nine, ten]] !! (1000000 - 1)
                   where all = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

-- Project Euler: Problem 25
fibs :: [Integer]
fibs = 1 : 1 : zipWith (+) fibs (tail fibs)

ans25 :: Int -> Integer
ans25 n = fst . head . dropWhile (\(num, l) -> l < n) . zip [1..] . map (length . show) $ fibs

-- Project Euler: Problem 26
divAns :: Int -> [(Int, Int)]
divAns num = unfoldr (\(ns, rem) -> 
                        let  dividend  = rem * 10
                             quotient  = dividend `div` num
                             remainder = dividend `mod` num 
                        in   if rem `elem` ns then Nothing else Just ((quotient, remainder), ((ns ++ [rem]), remainder))) 
                     ([], 1)
largestRecurSeq :: Int -> [Int]
largestRecurSeq num = 
  let quorems = divAns num
      quos    = map fst quorems
      rems    = map snd quorems
      lastquo = ((last rems) * 10) `div` num 
  in  if (last rems) == 0 then [] else (lastquo) : (tail $ dropWhile (/= (lastquo)) quos)

ans26 :: Int
ans26 = fst . head . reverse . sortBy (compare `on` snd) . zip nums . map (length . largestRecurSeq) $ nums
  where nums = [1..999]

-- Project Euler: Problem 27
ans27 :: (Integer, Integer)
ans27 = (\(p, q, _) -> (p, q)) . head . reverse . sortBy (compare `on` (\(_, _, z) -> z)) $ [(a, b, pSeq a b) | a <- as, b <- bs]
  where
    bs  = (primesUpTo 1000) ++ (map (*(-1)) (primesUpTo 1000))
    as  =  [-999, -998..999]
    pSeq x y = length . takeWhile (isPrime.abs) . map (\n -> n*n + x*n +y) $ [0..]


-- Project Euler: Problem 28
spiral :: Int -> [[Int]]
spiral 1 = [[1]]
spiral n = if n `mod` 2 == 0 then addEvenLinks nums (spiral $ n-1) else addOddLinks nums (spiral $ n-1)
  where nums = [(1+(n-1)^2)..(n^2)]

addEvenLinks :: [Int] -> [[Int]] -> [[Int]]
addEvenLinks ns = map reverse . reverse . addOddLinks ns . reverse . map reverse

addOddLinks :: [Int] -> [[Int]] -> [[Int]]
addOddLinks ns spr =  ((drop (length spr) ns):) . reverse . zipWith (:) ns . reverse $ spr

addDiagonals :: [[Int]] -> Int
addDiagonals spr = (sum $ (diagonal spr) ++ (diagonal . map reverse $ spr)) - correction
  where diagonal nss = map (\n -> (nss !! n) !! n) . take (length spr) $ [0..]
        correction = if (odd . length $ spr) then 1 else 0

ans28 :: Int
ans28 = addDiagonals . spiral $ 1001

ans28' :: Int -> Int
ans28' n = sum . scanl (+) term . concat . map (\x -> [x, x, x, x]) . take (n') $ nums
  where nums       = if odd n then [2, 4..] else [3, 5..]
        term       = if odd n then 1 else 0
        n'         = n `div` 2

-- Project Euler: Problem 29
ans29 :: Int
ans29 = length . nub . sort $ [a^b | a <- [2, 3..100], b <- [2, 3..100]]

-- Project Euler: Problem 30
ans30 :: Int -> Int
ans30 n =  sum . map fst .filter (\(n, s) -> n == s) . zip nums . map (sum . map (^n)) . map (map chrToInt . show) $ nums
  where nums = [10..upperLimit]
        upperLimit = fst . head . dropWhile (\(s, ps) -> s <= ps) . map (\n' -> (10^n' - 1, n'*(9^n))) $ [2, 3..]

-- Project Euler: Problem 31
-- takes a denomination, and (amount consumed so far, a target amount, [(number of coins, denomination)]) and 
-- returns a [(amount so far, remaining amount, [number of coins, denomination])] 
applyAmt :: Int -> (Int, Int, [(Int, Int)]) -> [(Int, Int, [(Int, Int)])]
applyAmt d (consAmt, amt, cs) = map (\nc -> (consAmt + nc*d, amt - d*nc, (nc, d): cs)) $ [0..(amt `div` d)]

numCombos :: Int ->Int 
numCombos tgtAmt = length . filter (\(_, r, _) -> r == 0) . foldl (>>=) (return (0, tgtAmt, [])) . map applyAmt $ [200, 100, 50, 20, 10, 5, 2, 1] 

-- Project Euler: Problem 32

powerset :: [a] -> [[a]]
powerset = filterM (\_ -> [True, False]) 

digChoices :: (Eq a) => [a] -> [[a]]
digChoices = concat . map permute . powerset

allDigChoices :: (Eq a) => [a] -> [([a], [a], [a])]
allDigChoices digits = [ (mplicandc, mplierc, prodc) | mplicandc <- digChoices digits, mplierc <- digChoices (digits \\ mplicandc), let prodc = (digits \\ mplicandc) \\ mplierc ]

filteredDigChoices :: [Int] -> [(Int, Int, Int)] 
filteredDigChoices digits  = [(mc, mp, pd) | (mcandc, mplierc, prodc) <- allDigChoices digits, mc' <- permute mcandc, mp' <- permute mplierc, pd' <- permute prodc,
                                             let mc = if null mc' then 0 else (read . concat . map show $ mc'), 
                                             let mp = if null mp' then 0 else (read . concat . map show $ mp'), 
                                             let pd = if null pd' then 0 else (read . concat . map show $ pd'),
                                             mc <= pd, mp <= pd, mc <= mp, mc > 0, mp > 0, pd > 0, mc * mp == pd]

permute :: (Eq a) => [a] -> [[a]]
permute [] = [[]]
permute ts = [ (t:rperm)| t <- ts, rperm <- permute (ts \\ [t])]

breakIntoTwo :: [a] -> [([a], [a])]
breakIntoTwo []  = [([], [])]
breakIntoTwo [x] = [([x], [])]
breakIntoTwo [x, y] = [([x], [y])]
breakIntoTwo (x:y:zs) = ([x], y:zs) : (map (\(m1, m2) -> ((x:m1), m2)) (breakIntoTwo (y:zs)))

filtCombos :: [Int] -> [(Int, Int, Int)]
filtCombos digits = [ (m1, m2, pd) | seq <- permute digits, (m1c, rs) <- breakIntoTwo seq, (m2c, pdc) <- breakIntoTwo rs ,
                            (not . null $ m1c), (not . null $ rs), (not . null $ m2c), (not . null $ pdc),
                            let m1 = read . concat . map show $ m1c,
                            let m2 = read . concat . map show $ m2c,
                            let pd = read . concat . map show $ pdc, 
                            m1 <= m2, m1 < pd, m2 < pd, m1 * m2 == pd]

ans32 :: Int
ans32 = sum . nub . map (\(_, _, p) -> p) . filtCombos $ [1, 2, 3, 4, 5, 6, 7, 8, 9]

-- Project Euler: Problem 33
lameCancel :: (Int, Int) -> (Int, Int)
lameCancel (n, d) = 
  let ns = show n
      ds = show d 
      ndiff = if (null $ ns \\ ds) then "1" else ns \\ ds
      ddiff = if (null $ ds \\ ns) then "1" else ds \\ ns
  in  (read ndiff, read ddiff)

lameRatios :: [(Int, Int)]
lameRatios = map fst . filter (\((rn, rd), (crn, crd)) -> (fromIntegral rn/fromIntegral rd) == (fromIntegral crn/fromIntegral crd)) 
                . filter (\(r, cr) -> r /= cr) 
                . zip rats . map lameCancel $ rats
  where rats = [(a, b) | a <- nums, b <- nums, a < b, notContain0 a && notContain0 b]
        notContain0 x = not . elem '0' . show $ x
        nums = [11..99]

ans33 :: Int
ans33 = denominator $ (product . map fst $ lameRatios) % (product . map snd $ lameRatios)

-- Project Euler: Problem 34
ans34 :: Int
ans34 = sum . map fst . filter (\(n, sf) -> n == sf) . zip nums . map (sum . map fact' . map chrToInt . show) $ nums
  where nums = [10..((10^upperLimit) - 1)]
        upperLimit = fst . head . dropWhile (\(_, (lhsLim, rhsLim)) -> lhsLim < rhsLim) . zip [1..] . map lim' $ [1..] 
        lim' n = (10^n - 1, n * (foldl1 (*) [1..9]))
        fact' 0 = 1 ; fact' 1 = 1 ; fact' 2 = 2 ; fact' 3 = 6 ; fact' 4 = 24 ; fact' 5 = 120 ; fact' 6 = 720
        fact' 7 = 5040 ; fact' 8 = 40320 ; fact' 9 = 362880 

-- Project Euler: Problem 35
ans35 :: Int
ans35 = length . map fst . filter (\(_, bv) -> bv == True) . zip candidatePrimes . map (all (`elem` candidatePrimes)) . map rotations $ candidatePrimes
  where candidatePrimes = primesUpTo 999999

rotations :: (Show a, Read a) => a -> [a]
rotations n = map read . map (\x -> (drop x n') ++ (take x n')) $ [0..(length n' - 1)]
  where n' = show n

-- Project Euler: Problem 36
ans36 :: Int
ans36 = sum . map fst . filter (\(n, b) -> (isPalindrome .show $ n) && (isPalindrome b)) . zip nums . map (\n -> showIntAtBase 2 intToDigit n "") $ nums 
  where nums = [1..999999]

-- Project Euler: Problem 37
lTruncCombos :: (Read a, Show a) => [a] -> [[a]]
lTruncCombos = tail . init . tails

rTruncCombos :: (Read a, Show a) => [a] -> [[a]]
rTruncCombos = map reverse . lTruncCombos . reverse 

isTruncPrime :: Integer -> Bool
isTruncPrime n = all isPrime . map read $ (lTruncCombos.show $ n) ++ (rTruncCombos.show $ n)

ans37 :: Integer
ans37 = sum . take 11 . drop 4 . map fst . filter (\(_, bv) -> bv == True) . zip primeNumbers. map isTruncPrime  $ primeNumbers

-- Project Euler: Problem 38
concatProd :: Int -> [Int] -> Int
concatProd num = read . concat . map (show . (num*)) 

constructNums :: [Int] -> [[Int]]
constructNums [] = [[]]
constructNums digs = [ (n:rs) | n <- digs, rs <- constructNums (digs \\ [n]) ]

nineDigPands :: [Int]
nineDigPands = map (read . concat . map show). constructNums $ [9, 8, 7, 6, 5, 4, 3, 2, 1]

-- only will test up to 5 dig nums, since n is minimum 2
-- also since num is minimum 1, we will test up to n == 9
-- returns Maybe (num, n) where amicp = concatProd num [1..n]
getConcatProd :: Int -> Maybe (Int, Int)
getConcatProd amicp = if null candidates then Nothing else Just (head candidates)
  where candidates = [(pn, last cs) | pn <- prodNum, cs <- (tail . inits $ nCands), (concatProd pn cs) == amicp] 
        prodNum = [9999, 9998..1]  -- this is the num in concatProd
        nCands  = [1..9]     -- this is the ns in concatProd

ans38 :: Int
ans38 =  (\(Just (n, c)) -> concatProd n [1..c]) . head . dropWhile (==Nothing) . map getConcatProd $ nineDigPands

-- Project Euler: Problem 39
rghtTri :: Int -> [(Int, Int, Int)]
rghtTri n = [ (a, b, c) | let sides = [1..n], a <- sides, b <- sides, c <- sides, a < b, b < c, a^2 + b^2 == c^2, a+b+c == n]

ans39 :: Int
ans39 = fst . head . reverse . sortBy (compare `on` snd) . zip triPers . map length . map rghtTri $ triPers
  where triPers = [3..1000]

-- Project Euler: Problem 40
ans40 = product . map chrToInt . map (str !!) . map (+ (-1)) $ [1, 10, 100, 1000, 10000, 100000, 1000000]
  where str = concat . map show $ [1..]

-- Project Euler: Problem 41
nDigPands :: Int -> [Int]
nDigPands n = map read . permute . concat . map show $ [n, n-1..1]

ans41 :: Int
ans41 = fst . head . filter ((==True).snd). zip allPands . map (isPrime.fromIntegral) $ allPands
 where allPands = concat . map nDigPands $ [9, 8..2]

-- Project Euler: Problem 42
word2Num :: String -> Int
word2Num = sum . map (\c -> ord c - ord 'A' + 1)

ans42 :: String -> String
ans42 txt = show . length . filter ( `elem` relevantTriNums) $ wordNums
  where wordNums = map word2Num . words $ txt
        relevantTriNums = takeWhile (<= (maximum wordNums)) . map fromIntegral $ triNums

main42 = interact $ ans42 . map (\c -> if c == ',' then ' ' else c) . filter (/= '"')

-- Project Euler: Problem 43
pands0To9 :: [String]
pands0To9 = permute "9876543210"

hasPeculiarProperty :: String -> Bool
hasPeculiarProperty ss = and . map ($ ss) . map (\(d, p) -> (==0) . (`mod` p) . read . take 3 . drop d) 
                               $ [(1, 2), (2, 3), (3, 5), (4, 7), (5, 11), (6, 13), (7, 17)] 

ans43 :: Int
ans43 = sum . map read . filter hasPeculiarProperty $ pands0To9


main :: IO ()
main = putStrLn $ show ans14
