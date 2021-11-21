{-# OPTIONS --safe #-}
module Sprintf where

open import Data.Char
open import Data.Integer
open import Data.Float
open import Data.String
open import Data.List hiding ( _++_ )

open import Relation.Binary.PropositionalEquality
open import Relation.Nullary
open import Data.Empty

data Format : Set where
  addEnd : Format
  addString : String → Format → Format
  addℤ : Format → Format
  addFloat : Format → Format
  addChar : Format → Format

format→Type : Format → Set
format→Type addEnd = String
format→Type (addString s f) = format→Type f
format→Type (addℤ f) = ℤ → format→Type f
format→Type (addFloat f) = Float → format→Type f
format→Type (addChar f) = Char → format→Type f

sprintfType : List Char -> Format
sprintfType [] = addEnd
sprintfType ('%' ∷ '%' ∷ s) = addString "%" (sprintfType s)
sprintfType ('%' ∷ 'd' ∷ s) = addℤ (sprintfType s)
sprintfType ('%' ∷ 'f' ∷ s) = addFloat (sprintfType s)
sprintfType ('%' ∷ 'c' ∷ s) = addChar (sprintfType s)
sprintfType (c ∷ s) = addString (fromList (c ∷ [])) (sprintfType s) 

sprintf' : (f : Format) → String → format→Type f
sprintf' addEnd acc = acc
sprintf' (addString x f) acc = sprintf' f (acc ++ x)
sprintf' (addℤ f) acc = λ x → sprintf' f (acc ++ Data.Integer.show x)
sprintf' (addFloat f) acc = λ x → sprintf' f (acc ++ Data.Float.show x)
sprintf' (addChar f) acc = λ x → sprintf' f (acc ++ fromList (x ∷ []))

sprintf : (s : String) → format→Type (sprintfType (toList s))
sprintf s = sprintf' (sprintfType (toList s)) ""

_ : sprintfType (toList "%c%f%d%") ≡ addChar (addFloat (addℤ (addString "%" addEnd)))
_ = refl

-- Should accept no arg when no fmt
_ : sprintf "" ≡ ""
_ = refl

-- Should format integers/char/float/%
_ : sprintf "%c%f%d%" 'a' 123.0  -[1+ 3 ] ≡ "a123.0-4%"
_ = refl


-- Should format integers/char/float/%
_ : sprintf "%d %f" -[1+ 3 ] 666.6 ≡ "-4 666.6"
_ = refl
