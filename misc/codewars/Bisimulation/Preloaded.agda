{-# OPTIONS --cubical --safe #-}
module Preloaded where

open import Cubical.Core.Everything
open import Cubical.Foundations.Everything
open import Cubical.Data.Everything
open import Data.List
open import Preloaded


data W (A : Set) (B : A → Set) : Set where
  sup : (a : A) → (B a → W A B) → W A B

ℕᵂ : Set
ℕᵂ = W Bool λ {false → ⊥ ; true → Unit}

Listᵂ : Set → Set
Listᵂ A = W (Unit ⊎ A) λ {(inl _) → ⊥ ; (inr _) → Unit}
