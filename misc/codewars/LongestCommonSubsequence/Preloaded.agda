{-# OPTIONS --safe #-}
module Preloaded where

open import Data.List
open import Data.Nat
open import Data.Product
open import Relation.Nullary
open import Relation.Binary.PropositionalEquality
open import Relation.Binary.Core
open import Relation.Binary

data Subseq {n} { A : Set n } : List A → List A → Set where
  subseq-nil : Subseq [] []
  subseq-take : ∀ a xs ys → Subseq xs ys → Subseq (a ∷ xs) (a ∷ ys)
  subseq-drop : ∀ a xs ys → Subseq xs ys → Subseq xs (a ∷ ys)

is-lcs : ∀ {n} {A : Set n} → List A → List A → List A → Set n
is-lcs zs xs ys =
  (Subseq zs xs × Subseq zs ys) ×
  (∀ ts → Subseq ts xs → Subseq ts ys → length ts ≤ length zs)

longest : ∀ {n} {A : Set n} → List A → List A → List A
longest s1 s2 with length s1 ≤? length s2
... | yes _ = s2
... | no _ = s1

lcs : ∀ {n} {A : Set n} → Decidable {A = A} _≡_ → List A → List A → List A
lcs _ [] _ = []
lcs _ _ [] = []
lcs dec (x ∷ xs) (y ∷ ys) with dec x y
... | yes _ = x ∷ lcs dec xs ys
... | no _ = longest (lcs dec (x ∷ xs) ys) (lcs dec xs (y ∷ ys))
