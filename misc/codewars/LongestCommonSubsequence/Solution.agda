{-# OPTIONS --safe #-}
module Solution where

open import Data.List
open import Data.Nat
open import Data.Nat.Properties
open import Data.Product
open import Relation.Nullary
open import Relation.Binary.PropositionalEquality
open import Relation.Binary.Core
open import Preloaded

lcs-correct : ∀ {n} {A : Set n} (dec : Decidable {A = A} _≡_) (xs ys : List A) → is-lcs (lcs dec xs ys) xs ys
lcs-correct dec xs ys = ?
