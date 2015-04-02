import Data.List

data Lights = L1 | L2 | L3 | L4 | L5 | L6 deriving (Eq, Ord, Show)

data Switches = S1 | S2 | S3 deriving (Eq, Ord, Show)

-- when switches are pressed repeatedly, what is the expected outcome
-- position in list is # times that switch is pressed, data is which switches are lit up
seqS1 :: [[Lights]]
seqS1 = [[], [L2, L3], [L4, L6], [L1, L3], [L2, L6]]

seqS2 :: [[Lights]]
seqS2 = [[], [L1, L5], [L3, L6], [L1, L4], [L2, L5]]

seqS3 :: [[Lights]]
seqS3 = [[], [L2, L4], [L3, L5], [L1, L2], [L4, L5]]

-- to construct all sequences of switch presses of length n
constructSeqLen :: Int -> [[Switches]]
constructSeqLen 0 = [[]]
constructSeqLen n = concat $ map (\seq -> [seq ++ [S1], seq ++ [S2], seq ++ [S3]]) $ constructSeqLen (n-1)

-- cum seq, will create all sequences upto length specified
-- i.e. all 0-length seq, all 1-length seq, ..., all n-length seq
constructCumSeq :: Int -> [[Switches]]
constructCumSeq 0 = [[]]
constructCumSeq n = constructCumSeq (n-1) ++ constructSeqLen n

getLightsFor :: [[Lights]] -> Int -> [Lights]
getLightsFor ls n
	| n < 0 || n >= (length ls) 	= []
	| otherwise 			= ls !! n

-- takes a list of switch presses, and resolves it into a list of lights that are lit up
resolveSwitchSeq :: [Switches] -> [Lights]
resolveSwitchSeq = resolveSwitchSeq' (0, 0, 0) []

resolveSwitchSeq' :: (Int, Int, Int) -> [Lights] -> [Switches] -> [Lights]
resolveSwitchSeq' (s1n, s2n, s3n) ls [] = ls	-- if no more switches to consume, lights stay as they are
resolveSwitchSeq' (s1n, s2n, s3n) ls (s:ss)
	| s1n >= (length seqS1)  || s2n >= (length seqS2) || s3n >= (length seqS3)	
		= resolveSwitchSeq' (0, 0, 0) [] ss	-- more than 4 presses of anything resets all
	| s1n < 0 || s2n < 0 || s3n < 0		
		= []					-- error condition, should never happen
	| s == S1 = resolveSwitchSeq' (s1n+1, s2n, s3n) (sort.nub $ (getLightsFor seqS1 (s1n + 1)) ++ (getLightsFor seqS2 s2n) ++ (getLightsFor seqS3 s3n)) ss
	| s == S2 = resolveSwitchSeq' (s1n, s2n+1, s3n) (sort.nub $ (getLightsFor seqS1 s1n) ++ (getLightsFor seqS2 (s2n + 1)) ++ (getLightsFor seqS3 s3n)) ss
	| s == S3 = resolveSwitchSeq' (s1n, s2n, s3n+1) (sort.nub $ (getLightsFor seqS1 s1n) ++ (getLightsFor seqS2 s2n) ++ (getLightsFor seqS3 (s3n + 1))) ss 

playGame :: [Switches]
playGame = 
  let cumSeq = constructCumSeq 12
      ans = dropWhile (\(ss, ls) -> ls /= [L1, L2, L3, L4, L5, L6]) $ zip cumSeq $ map resolveSwitchSeq cumSeq
  in  if (null ans) then [] else (fst.head) ans

main :: IO ()
main = do
 	 let a = playGame
	 putStrLn (show a)
