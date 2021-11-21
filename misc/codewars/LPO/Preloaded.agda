{-# OPTIONS --safe #-}
module Preloaded where

open import Relation.Nullary
open import Relation.Binary.PropositionalEquality
open import Data.Sum
open import Data.Product
open import Data.Bool
open import Data.Nat

even : ℕ → Bool
even 0 = true
even (suc n) = not (even n)

EM = (A : Set) → A ⊎ ¬ A

LPO = (f : ℕ → Bool) → (∀ n → f n ≡ false) ⊎ (∃ λ n → f n ≡ true)

LLPO = (f : ℕ → Bool) → (∀ n m → n ≢ m → f n ≡ false ⊎ f m ≡ false) →
  (∀ n → even n ≡ true → f n ≡ false) ⊎ (∀ n → even n ≡ false → f n ≡ false)
