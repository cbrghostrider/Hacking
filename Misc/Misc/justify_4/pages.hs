
solve n = length $ takeWhile (<=n) $ map (sum $ (map (length $ show))) $ map (\x -> x [1, 2..]) $ map take [1, 2..]

main = solve 1095

