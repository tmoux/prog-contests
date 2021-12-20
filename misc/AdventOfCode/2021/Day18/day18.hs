module Main where

data SnailNum = Leaf Int | Branch SnailNum SnailNum

reduce :: SnailNum -> SnailNum
reduce = undefined

explode :: SnailNum -> SnailNum
explode = undefined


magnitude :: SnailNum -> Int
magnitude (Leaf x) = x
magnitude (Branch l r) = 3 * magnitude l + 2 * magnitude r

main :: IO ()
main = undefined
