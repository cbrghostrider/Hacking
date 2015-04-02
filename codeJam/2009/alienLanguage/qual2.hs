import System.Environment (getArgs)

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processQual ip)

-- a token is a list of strings, list length is #chars per dict word
type Token = [String]

-- a dict is a list of words
type Dict  = [String]

-- takes string made up so far for curr token
-- and unconsumed input
-- returns (string for curr token, rest of unconsumed input)
consumeLtr :: String -> String -> (String, String)
consumeLtr strSoFar [] = (strSoFar, [])
consumeLtr strSoFar (')':xs) = (strSoFar, xs)
consumeLtr strSoFar (x:xs) = consumeLtr (strSoFar ++ [x]) xs

-- takes partial output, unconsumed input, and returns full output
consumeLtrStart :: [String] -> String -> [String]
consumeLtrStart strs [] = strs
consumeLtrStart strs ('(': xs) = 
  let (myStr, restStr) = consumeLtr "" xs in consumeLtrStart (strs ++ [myStr]) restStr
consumeLtrStart strs (x:xs) = consumeLtrStart (strs ++ [[x]]) xs

-- checks if a word can be formed from token
isWordInToken :: (String, Token) -> Bool
isWordInToken (s, t) = all (==True) . map (\(letter, choices) -> letter `elem` choices) $ zip s t

-- converts a string to a Token
-- e.g. (ab)c(bc) -> ["ab", "c", "bc"]
convert :: String -> Token
convert = consumeLtrStart [] 

-- given a Dict and a Token, lists how many words from that token in dict
listNum :: Dict -> Token -> Int
listNum d t = length . filter (== True) . map isWordInToken $ zip d (repeat t)  

toOpStr :: Int -> [Int] -> [String]
toOpStr n [] = []
toOpStr n (x:xs) = ("Case #" ++ (show n) ++ ": " ++ (show x)) : toOpStr (n+1) xs

processQual :: String -> String
processQual ip = 
  let allLines = lines ip
      [l, d, n]= map read . words . head $ allLines
      dict     = take d . tail $ allLines
      tokens   = map convert . take n . drop d . tail $ allLines
      nums     = map (listNum dict) tokens
      opLines  = toOpStr 1 nums
  in  unlines opLines
      

