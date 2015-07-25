-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
toWords :: [String]
toWords = ["o' clock", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
          ,"ten", "eleven", "twelve", "thirteen", "fourteen", "quarter", "sixteen", "seventeen", "eighteen", "nineteen"
          ,"twenty", "twenty one", "twenty two", "twenty three", "twenty four", "twenty five"
          , "twenty six", "twenty seven", "twenty eight", "twenty nine", "half"]

timeInWords :: Int -> Int -> String
timeInWords h m = 
  let hrwords   = toWords !! h
      hrwords2  = if h == 12 then (toWords !! 1) else (toWords !! (h+1))
      minwords  = toWords !! m
      minwords2 = toWords !! (60 - m)
      token     = if m == 15 || m == 30 || m == 45 then "" else "minutes "
  in  if m == 0 
         then unwords [hrwords, minwords]
         else if m > 30
                 then unwords [minwords2, (token ++ "to"), hrwords2]
                 else unwords [minwords, (token ++ "past"), hrwords]

main :: IO ()
main = do
  hstr <- getLine
  mstr <- getLine
  putStrLn $ timeInWords (read hstr) (read mstr)
