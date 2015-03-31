
import Misc

toWord :: Int -> String
toWord 1 = "one"
toWord 2 = "two"
toWord 3 = "three"
toWord 4 = "four"
toWord 5 = "five"
toWord 6 = "six"
toWord 7 = "seven"
toWord 8 = "eight"
toWord 9 = "nine"
toWord 10 = "ten"
toWord 11 = "eleven"
toWord 12 = "twelve"
toWord 13 = "thirteen"
toWord 14 = "fourteen"
toWord 15 = "fifteen"
toWord 16 = "sixteen"
toWord 17 = "seventeen"
toWord 18 = "eighteen"
toWord 19 = "nineteen"
toWord 20 = "twenty"
toWord 30 = "thirty"
toWord 40 = "forty"
toWord 50 = "fifty"
toWord 60 = "sixty"
toWord 70 = "seventy"
toWord 80 = "eighty"
toWord 90 = "ninety"
toWord 100 = "hundred"
toWord 1000 = "thousand"

stringify :: Int -> String
stringify num = 
  let lowTwenty = if lowerTwo > 0 && lowerTwo <= 20 then toWord lowerTwo else ""  -- special case for low Twenty
      lowStr    = if low /= 0 then toWord low else ""
      tenStr    = if ten /= 0 then toWord ten else ""
      hundStr   = if hund /= 0 then (toWord (hund `div` 100)) ++ " " ++ toWord 100 else ""
      thouStr   = if thou /= 0 then (toWord (thou `div` 1000)) ++ " " ++ toWord 1000 else ""
      andStr    = if (lowStr /= "" || tenStr /= "" || lowTwenty /= "") && (hundStr /= "" || thouStr /= "") then "and" else ""
      low       = num `mod` 10
      ten       = num `mod` 100 - num `mod` 10
      hund      = num `mod` 1000 - num `mod` 100
      thou      = num `mod` 10000 - num `mod` 1000
      lowerTwo  = num `mod` 100
      lowTwoDigStr = if lowTwenty /= "" then lowTwenty else tenStr ++ " " ++ lowStr
  in  thouStr ++ " " ++ hundStr ++ " " ++ andStr ++ " " ++ lowTwoDigStr 

ans17 :: Int
ans17 = sum . map length . map (concat.words) . map stringify $ [1..1000]

