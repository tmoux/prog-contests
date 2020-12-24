module Day4 where

import Text.ParserCombinators.Parsec
import Text.ParserCombinators.Parsec.Char

parseFile = many parsePassport
parsePassport = manyTill (parseID `sepBy` (many1 space)) (try doubleNewline)
doubleNewline = count 2 newline
parseID :: Parser (String,String)
parseID = do
  id <- count 3 letter
  char ':'
  val <- many1 (alphaNum <|> char '#')
  return (id,val)

main = do
  input <- readFile "in"
  let passports =
          case parse parsePassport "" input of
            Left err -> error (show err)
            Right x -> x
  putStrLn (show passports)
