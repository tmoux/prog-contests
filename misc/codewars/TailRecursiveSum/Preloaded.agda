{-# OPTIONS --safe #-}
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
