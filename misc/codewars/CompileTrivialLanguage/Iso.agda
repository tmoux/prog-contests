{-# OPTIONS --safe #-}
module Iso where

open import Relation.Binary.PropositionalEquality public
open import Data.Nat public

record _⇔_ (A B : Set) : Set where
  constructor Bijection
  field
    A→B : A → B
    B→A : B → A
    A→B→A : ∀ (a : A) → B→A (A→B a) ≡ a
    B→A→B : ∀ (b : B) → A→B (B→A b) ≡ b

data ℕ+1 : Set where
  null : ℕ+1
  nat : ℕ → ℕ+1

data ℕ+ℕ : Set where
  left : ℕ → ℕ+ℕ
  right : ℕ → ℕ+ℕ
