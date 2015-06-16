-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Control.Monad
import Data.Maybe
import qualified Data.Map as Map

type DictMap  = Map.Map String String

isMultiCast :: String -> Bool
isMultiCast = (`elem` "13579bdf") . (!! 1)

isUniCast :: String -> Bool
isUniCast = not . isMultiCast

macLearning :: DictMap -> String -> String -> String -> (String, DictMap)
macLearning dict pin dadd sadd = 
  let ndict = Map.insert sadd pin dict
      pout  = Map.lookup dadd ndict
      pout' = fromMaybe "" pout
  in  if isMultiCast sadd 
         then ("drop", dict) 
         else if isMultiCast dadd || pout == Nothing 
                 then ("flood", ndict) 
                 else if pin == pout' 
                         then ("drop", ndict) 
                         else (pout', ndict)

runTests :: DictMap -> Int -> IO (DictMap)
runTests dict 0 = return dict
runTests dict _ = do
  ip <- getLine
  let [pstr, dadd, sadd] = words ip
  let (opstr, odict) = macLearning dict pstr dadd sadd
  putStrLn opstr
  return odict

main :: IO ()
main = do 
  nstr <- getLine
  let dict = Map.empty
  let n    = read nstr
  foldM_ runTests dict [n, (n-1)..0]
