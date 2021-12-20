{-# LANGUAGE PatternSynonyms #-}

module Main where

data Packet = PacketLit Int Int | PacketOp Int [Packet] 

pattern B0 :: Bool
pattern B0 = False
pattern B1 :: Bool
pattern B1 = True

{-# COMPLETE B0, B1 #-}
asd :: Bool -> Bool
asd d = case d of
    B0 -> True
    B1 -> False

binary_string :: String -> [Bool]
binary_string = concatMap f
  where f '0' = [B0, B0, B0, B0]
        f '1' = [B0, B0, B0, B1]
        f '2' = [B0, B0, B1, B0]
        f '3' = [B0, B0, B1, B1]
        f '4' = [B0, B1, B0, B0]
        f '5' = [B0, B1, B0, B1]
        f '6' = [B0, B1, B1, B0]
        f '7' = [B0, B1, B1, B1]
        f '8' = [B1, B0, B0, B0]
        f '9' = [B1, B0, B0, B1]
        f 'A' = [B1, B0, B1, B0]
        f 'B' = [B1, B0, B1, B1]
        f 'C' = [B1, B1, B0, B0]
        f 'D' = [B1, B1, B0, B1]
        f 'E' = [B1, B1, B1, B0]
        f 'F' = [B1, B1, B1, B1]
        f _ = error "Unexpected char"

main :: IO ()
main = do
    line <- getLine
    let code = binary_string line
    print $ code