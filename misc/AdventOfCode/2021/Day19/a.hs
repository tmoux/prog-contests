-- https://gitlab.com/sakisan/adventofcode/-/blob/2021/Haskell/Day19.hs
{-# LANGUAGE TupleSections #-}

import Data.Either (partitionEithers)
import Data.List (nub, permutations, transpose)
import Data.List.Split (splitOn)
import Data.Map (Map)
import qualified Data.Map as Map

main = interact $ solve . parse

solve (x:xs) = "Part1: " ++ show part1 ++ "\nPart2: " ++ show part2 ++ "\n"
  where
    aligned = align [(x, [0, 0, 0])] [x] xs
    part1 = length . nub . concat . map fst $ aligned
    part2 = maximum . map (uncurry manhattan) . pick2 . map snd $ aligned

type Pos = [Int]
type Scanner = [Pos]

parse = map (map parsePos . tail) . splitOn [""] . lines
parsePos = map read . splitOn ","

align :: [(Scanner, Pos)] -> [Scanner] -> [Scanner] -> [(Scanner, Pos)]
align result _ [] = result
align result (ref:refs) scanners = align (found ++ result) (map fst found ++ refs) notFound
  where (found, notFound) = partitionEithers
          [ maybe (Right scanner) Left . safeHead $ align2 ref scanner
          | scanner <- scanners
          ]

align2 :: Scanner -> Scanner -> [(Scanner, Pos)]
align2 a b = [(map (add pos) o, pos) | o <- orientations b, pos <- overlap a o]

overlap :: Scanner -> Scanner -> [Pos]
overlap as bs = Map.keys . Map.filter (>= 12) . Map.fromListWith (+) . map (, 1) $ 
                diff <$> as <*> bs

orientations :: Scanner -> [Scanner]
orientations ps = transpose $ map orientationsPos ps

orientationsPos :: Pos -> [Pos]
orientationsPos p = scanl (flip ($)) p steps
  -- https://stackoverflow.com/questions/16452383/how-to-get-all-24-rotations-of-a-3-dimensional-array
  where steps = [r,t,t,t,r,t,t,t,r,t,t,t, r.t.r.r, t,t,t,r,t,t,t,r,t,t,t]
        r [x,y,z] = [x,z,-y]
        t [x,y,z] = [-y,x,z]

safeHead :: [a] -> Maybe a
safeHead [] = Nothing
safeHead (x:_) = Just x

pick2 :: [a] -> [(a,a)]
pick2 [] = []
pick2 (x:xs) = map (x ,) xs ++ pick2 xs

manhattan :: Pos -> Pos -> Int
manhattan a b = sum $ map abs $ diff a b
 
diff :: Pos -> Pos -> Pos
diff = zipWith (-)

add :: Pos -> Pos -> Pos
add = zipWith (+)
