{-# OPTIONS --cubical --safe #-}
module Solution where

open import Cubical.Core.Everything
open import Cubical.Foundations.Everything
open import Cubical.Data.Everything
open import Data.List
open import Preloaded

{- Proloaded:
data W (A : Set) (B : A → Set) : Set where
  sup : (a : A) → (B a → W A B) → W A B

ℕᵂ : Set
ℕᵂ = W Bool λ {false → ⊥ ; true → Unit}

Listᵂ : Set → Set
Listᵂ A = W (Unit ⊎ A) λ {(inl _) → ⊥ ; (inr _) → Unit}
-}

ℕ≡ℕᵂ : ℕ ≡ ℕᵂ
ℕ≡ℕᵂ = ?


List≡Listᵂ : ∀ {A} → List A ≡ Listᵂ A
List≡Listᵂ = ?
