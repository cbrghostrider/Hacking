
main = putStrLn "What's your name?" >> getLine >>= \n -> putStrLn ("Hello " ++ n)

