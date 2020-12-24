module Main where

import Text.Parsec
import Text.Parsec.Combinator
import Text.Parsec.Number
import qualified Data.Map.Strict as Map
import System.Environment

data Rule 
  = Ch Char 
  | Seq [Int]
  | Alt [Rule]
  deriving (Show)

lineParser = do
  ln <- int
  string ": "
  rule <- ruleParser
  return (ln,rule)

ruleParser :: Parsec String () Rule
ruleParser = try ((\x y -> Alt [x,y]) <$> ruleParser2 <* string " | " <*> ruleParser2)
         <|> ruleParser2

ruleParser2 = Ch <$ char '"' <*> anyChar <* char '"'
         <|> try ((\x y -> Seq [x,y]) <$> int <* space <*> int)
         <|> (\x -> Seq [x]) <$> int

mkParser :: Map.Map Int Rule -> Rule -> Parsec String () String
mkParser mp rule = case rule of
  Ch c -> (pure c) <$ char c
  Seq xs -> go xs
    where go [x] = mkParser mp (mp Map.! x)
          go (x:xs) = (++) <$> mkParser mp (mp Map.! x) <*> go xs
  Alt rs -> go rs
    where go [r] = try (mkParser mp r)
          go (r:rs) = try (mkParser mp r) <|> go rs

main = do
  args <- getArgs
  rules <- lines <$> readFile (args !! 0)
  strings <- lines <$> readFile (args !! 1)
  let rule8 = (8, Alt [Seq [42],Seq [42,8]])
      rule11 = (11,Alt (fseq 20))
      fseq 0 = []
      fseq n = Seq (f n):fseq (n-1)
      f 1 = [42,31]
      f n = [42] ++ f (n-1) ++ [31]

  let rulesP = map parseL rules ++ [rule8,rule11]
  --let rulesP = map parseL rules
      mp = Map.fromList rulesP
      parsersMp = Map.map (mkParser mp) mp
      p0 = parsersMp Map.! 0
      ls = map (tryparse p0) strings
  mapM (\s -> putStrLn (s ++ ": " ++ (tryparseP p0 s))) strings
  print rulesP
  print (sum $ map fromEnum ls)
  where parseL :: String -> (Int,Rule)
        parseL l = case (parse lineParser "" l) of
                     Left err -> error (show err)
                     Right x -> x
        tryparse :: Parsec String () String -> String -> Bool
        tryparse p0 s = case (parse p0 "" s) of
                       Left err -> False
                       Right x -> x == s
        tryparseP :: Parsec String () String -> String -> String
        tryparseP p0 s = case (parse p0 "" s) of
                       Left err -> "n/a"
                       Right x -> x

