import qualified Data.Map as Map 
import Control.Monad
import Data.Maybe
import Data.List
import Data.Function

memoized_cl :: (Integral a, Num b, Ord a, Eq b) => Map.Map a b -> a -> (Map.Map a b, b)
memoized_cl m v = 
  let lk = Map.lookup v m
      (rm, rv') = memoized_cl m v'
      rv = rv' + 1
      v' = if v `mod` 2 == 0 then v `div` 2 else 3*v + 1
      retv = if lk == Nothing then rv else let Just ans = lk in ans
      retm  = if lk == Nothing then (Map.union (Map.insert v retv m) rm) else m
  in  (retm, retv)

ans14 :: Integer
ans14 = fst . head . reverse . sortBy (compare `on` snd.snd) . zip (1:nums) . scanl (memoized_cl . (\(m, _) -> m)) ((Map.singleton 1 1), 1) $ nums
  where nums = [1..999999]

main = do
  putStrLn $ "Number is: " ++ (show ans14)
{-

memoize :: (Ord a, Eq b) => (a -> b) -> Map.Map a b -> a -> (Map.Map a b, b)
memoize f m v = 
  let lk  = Map.lookup v m
      ret = if lk == Nothing then f v else let Just ans = lk in ans
      m2  = if lk == Nothing then let Just a = lk in Map.insert v a m else m
  in  (m2, ret)
-}
        {-
data MemoFun a b = MemoFun {runMemoFun :: a -> (Map.Map a b, b)}

instance (Ord a) => Monad (MemoFun a) where 
  return x = MemoFun (\a -> (Map.empty, x))
  MemoFun f >>= g = MemoFun $ \a -> let (m1, v1)  = f a
                                        MemoFun h = g v1
                                        mc = Map.unions . map (\(m, _) -> m) . map h . Map.keys $ m1
                                        (m2, v2)  = h a
                                    in  (Map.union mc m2, v2 )
 g :: \x -> MemoFun y -> (m2, z)
  M b -> (b -> M c)-> M c
  a -> (m, b) -> b -> a -> (m, c) -> a -> (m, c)
  -}

runMemoFun :: MemoFun (Map a b) (a->b) -> a -> b
runMemoFun (MemoFun mp fn) key = 
  let lk = Map.lookup key mp
      ret = if lk == Nothing then 

data MemoFun m f = MemoFun (m, f)

instance Monad (MemoFun m) where
  return g = MemoFun (empty, g)
  MemoFun (m1, g) >>= h = 

