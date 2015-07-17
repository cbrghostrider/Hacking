-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
isPrime :: Integer -> Bool
isPrime 0 = False
isPrime 1 = False
isPrime 2 = True
isPrime n = 
  let listChk = [2..endChk]
      endChk = (1 + (truncate.sqrt.fromIntegral $ n)) :: Integer
  in not . or . map (\x -> n `mod` x == 0) $ listChk 

ans3 :: Integer -> Integer
ans3 val = head . filter isPrime . filter (\x -> val `mod` x == 0) . reverse $ [1..newVal] 
  where newVal = val -- (1 + (val `div` 2)) :: Integer
  
main :: IO ()
main = do
  ip <- getContents
  let ns = map read . tail . lines $ ip
  mapM_ (putStrLn . show) $ map ans3 ns
