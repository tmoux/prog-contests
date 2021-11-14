{-# OPTIONS --safe #-}
module Sum where

open import Data.Nat
open import Data.Nat.Properties
open import Relation.Binary.PropositionalEquality
open import Preloaded

{-
Preloaded:

module Preloaded where

open import Data.Nat

sumSimple : (ℕ → ℕ) → ℕ → ℕ
sumSimple f zero = f zero
sumSimple f (suc n) = f (suc n) + sumSimple f n

sumAux : ℕ → (ℕ → ℕ) → ℕ → ℕ
sumAux acc f zero = f zero + acc
sumAux acc f (suc n) = sumAux (f (suc n) + acc) f n

sumTail : (ℕ → ℕ) → ℕ → ℕ
sumTail = sumAux zero
-}

sumEqLemma : (f : ℕ → ℕ) → (n : ℕ) → (acc : ℕ)
  → sumAux acc f n ≡ sumSimple f n + acc
sumEqLemma f zero acc = refl
sumEqLemma f (suc n) acc 
  rewrite sumEqLemma f n (f (suc n) + acc) | +-comm (f (suc n)) (sumSimple f n) | +-assoc (sumSimple f n) (f (suc n)) acc = refl

sumEq : (f : ℕ → ℕ) → (n : ℕ) → sumTail f n ≡ sumSimple f n
sumEq f n rewrite sym (+-identityʳ (sumSimple f n)) = sumEqLemma f n 0
