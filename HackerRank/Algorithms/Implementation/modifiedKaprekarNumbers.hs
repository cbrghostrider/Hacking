-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

isKaprekar :: Integer -> Bool
isKaprekar num = 
  let nsqr    = num * num
      nsqstr  = show nsqr
      nstr    = show num
      ndigs   = length nstr
      rightstr= reverse . take ndigs . reverse $ nsqstr
      leftstr = reverse . drop ndigs . reverse $ nsqstr
      lnum    = if null leftstr then 0 else read leftstr
      newnum  = (lnum) + (read rightstr)
  in  if newnum == num then True else False

kaprekar :: Integer -> Integer -> [Integer]
kaprekar p q = filter isKaprekar [p, (p+1)..q]

main :: IO ()
main = do 
  ip <- getContents
  let [p, q] = map read . lines $ ip
  let ns = kaprekar p q
  putStrLn $ if null ns then "INVALID RANGE" else (unwords . map show $ ns)
