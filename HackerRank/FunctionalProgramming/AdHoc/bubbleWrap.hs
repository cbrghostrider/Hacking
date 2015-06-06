-- Since the time to pop a bubble is 1, and the time for an unsuccessful attempt is 1, 
-- all we have to do is compute the expected number of attempts to pick ALL bubbles
-- For any bubble, the last attempt for a bubble is when it is popped, while all the attempts prior
-- on it are unsuccessful
-- 
-- Consider the bubble wrap initially, with no unpopped bubble. Obviously any bubble we pick
-- will be unpopped, with probability 1.
-- From the second bubble onwards, things get interesting. Now we have a finite chance of picking
-- unpopped bubbles...
-- So for popping the second bubble, consider that we randomly pick a bubble to pop.
-- Either we pick an unpopped bubble immediately, or, 
-- we pick a popped bubble, and then try again and pick an unpopped one, or
-- we pick a popped bubble, try again and pick a popped bubble again, and then pick an unpopped one, or.
-- ... and so on.
-- The expected number of attempts to pop the SECOND bubble is:
-- (mn-1)/mn + (1/mn) * (mn-1)/mn + ((1/mn)^2) * ((mn - 1) / mn) ...
-- = ((mn-1)/mn) * [(1/mn)^0 + (1/mn)^1 + (1/mn)^2 + .... ]
--
-- In general for the ith bubble, 
-- This is a geometric series a + ar + ar^2 + .... = a/(1-r)
-- with a = 1, r = (i/mn)                
-- So our expected time to pop the ith bubble = 1/(1- i/mn) = mn / (mn-i)
--
-- Now we just sum this from i = 0 to i = n*m, to get expected time to pop all bubbles.

expectedAttemptsIthUnpopped :: Int -> Int -> Int -> Double
expectedAttemptsIthUnpopped n m i = fromIntegral (m*n) / fromIntegral (m*n - i)

bubbleExpectedAttempts :: Int -> Int -> Double
bubbleExpectedAttempts n m = sum . map (expectedAttemptsIthUnpopped n m) . init $ [0..(n*m)]

computeExpectedTime :: Int -> Int -> Double
computeExpectedTime n m = bubbleExpectedAttempts n m

main :: IO ()
main = do
  nmstr <- getLine
  let [n, m] = map read . words $ nmstr
  putStrLn $ show $ computeExpectedTime n m

