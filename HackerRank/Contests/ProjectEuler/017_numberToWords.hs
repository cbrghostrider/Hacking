-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
toWord :: Int -> String
toWord 1 = "One"
toWord 2 = "Two"
toWord 3 = "Three"
toWord 4 = "Four"
toWord 5 = "Five"
toWord 6 = "Six"
toWord 7 = "Seven"
toWord 8 = "Eight"
toWord 9 = "Nine"
toWord 10 = "Ten"
toWord 11 = "Eleven"
toWord 12 = "Twelve"
toWord 13 = "Thirteen"
toWord 14 = "Fourteen"
toWord 15 = "Fifteen"
toWord 16 = "Sixteen"
toWord 17 = "Seventeen"
toWord 18 = "Eighteen"
toWord 19 = "Nineteen"
toWord 20 = "Twenty"
toWord 30 = "Thirty"
toWord 40 = "Forty"
toWord 50 = "Fifty"
toWord 60 = "Sixty"
toWord 70 = "Seventy"
toWord 80 = "Eighty"
toWord 90 = "Ninety"
toWord 100 = "Hundred"

stringify' :: Int -> Int -> String
stringify' 0 num = 
  let lowTwenty = if lowerTwo > 0 && lowerTwo <= 20 then toWord lowerTwo else ""  -- special case for low Twenty
      lowStr    = if low /= 0 then toWord low else ""
      tenStr    = if ten /= 0 then toWord ten else ""
      hundStr   = if hund /= 0 then (toWord (hund `div` 100)) ++ " " ++ toWord 100 else ""
      low       = num `mod` 10
      ten       = num `mod` 100 - num `mod` 10
      hund      = num `mod` 1000 - num `mod` 100
      thou      = num `mod` 10000 - num `mod` 1000
      lowerTwo  = num `mod` 100
      lowSpace = if tenStr /= "" && lowStr /= "" then " " else ""
      lowTwoDigStr = if lowTwenty /= "" then lowTwenty else tenStr ++ lowSpace ++ lowStr
      needSpace = if hundStr /= "" && lowTwoDigStr /= "" then " " else ""
  in  hundStr ++ needSpace ++  lowTwoDigStr 

stringify' n num = 
  let testVal  = 1000 ^ n
      upperNum = num `div` testVal
      restNum = num `mod` testVal
      choiceStr
        | n == 1 = "Thousand"
        | n == 2 = "Million"
        | n == 3 = "Billion"
  in  stringify upperNum ++ " " ++ choiceStr ++ " " ++ stringify restNum

stringify :: Int -> String
stringify num
  | num `div` 1000000000 /= 0 = stringify' 3 num
  | num `div` 1000000    /= 0 = stringify' 2 num
  | num `div` 1000       /= 0 = stringify' 1 num
  | otherwise                 = stringify' 0 num

main :: IO ()
main = do
  ip <- getContents
  let ns = map read . tail . lines $ ip
      anss = map stringify ns
  mapM_ (putStrLn) anss
