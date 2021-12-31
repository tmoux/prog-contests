module Macros where

open import Data.Nat
open import Relation.Binary.PropositionalEquality
open import Reflection

open import Data.Unit
open import Data.List using ([]; _∷_)
open import Data.Maybe using (Maybe; just; nothing; maybe′)


macro
    plus-to-times : Term → Term → TC ⊤
    plus-to-times (def (quote _+_) (a ∷ b ∷ [])) hole =
      unify hole (def (quote _*_) (a ∷ b ∷ []))
    plus-to-times v hole = unify hole v

thm : (a b : ℕ) → plus-to-times (a + b) ≡ a * b
thm a b = refl
