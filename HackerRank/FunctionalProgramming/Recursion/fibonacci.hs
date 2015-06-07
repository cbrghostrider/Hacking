-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
module Main where

fib 1 = 0
fib 2 = 1
fib n = fib (n-1) + fib (n-2)

main = do
    input <- getLine
    print . fib . (read :: String -> Int) $ input

