{-# OPTIONS --safe #-}
module Proof where

open import Relation.Binary.PropositionalEquality
open import Data.Nat
open import Data.Nat.Properties

invert : (a b : ℕ) → a + a ≡ b + b → a ≡ b
invert zero zero = λ _ → refl
invert (suc a) (suc b) eq
  rewrite (+-suc a a) | (+-suc b b) = cong suc (invert a b (cong pred (cong pred eq)))
