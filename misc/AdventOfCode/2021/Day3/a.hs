bv_to_int :: [Bool] -> Int
bv_to_int (True : xs) = 1 + 2 * bv_to_int xs
bv_to_int (False : xs) = 2 * bv_to_int xs
bv_to_int [] = 0



main = do
  print "Hello world" 
