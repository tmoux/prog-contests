{-# OPTIONS --safe #-}
module OddsAndEvens where

open import Preloaded
open import Data.Nat
open import Data.Nat.Properties

{- Preloaded code:

data Even : ℕ → Set
data Odd  : ℕ → Set

data Even where
  zero : Even zero
  suc  : ∀ {n : ℕ} → Odd n → Even (suc n)

data Odd where
  suc : ∀ {n : ℕ} → Even n → Odd (suc n)
  
-}

-- | Implement all these functions
infixl 6 _e+e_ _o+e_ _o+o_ _e+o_
_e+e_ : ∀ {m n : ℕ} → Even m → Even n → Even (m + n)
_o+e_ : ∀ {m n : ℕ} → Odd  m → Even n → Odd  (m + n)
_o+o_ : ∀ {m n : ℕ} → Odd  m → Odd  n → Even (m + n)
_e+o_ : ∀ {m n : ℕ} → Even m → Odd  n → Odd  (m + n)

zero e+e zero = zero
zero e+e suc x = suc x
suc {n} x e+e zero rewrite +-identityʳ n = suc x
suc {n} x e+e suc {m} y rewrite +-suc n m = suc (suc (x o+o y))

suc zero o+e zero = suc zero
suc (suc x) o+e zero = suc (suc (x o+e zero))
suc zero o+e suc y = suc (suc y)
suc (suc x) o+e suc y = suc (suc (x o+e suc y))

suc zero o+o suc zero = suc (suc zero)
suc zero o+o suc (suc x) = suc (suc (suc x))
suc (suc x) o+o suc zero = suc (suc (x o+o suc zero))
suc (suc x) o+o suc (suc x₁) = suc (suc (x o+o suc (suc x₁)))

zero e+o suc x = suc x
suc {n} x e+o suc {m} y rewrite +-suc n m = suc (suc (x o+e y))
