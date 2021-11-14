{-# OPTIONS --safe #-}
module FlipTreeSym where

open import Relation.Binary.PropositionalEquality
open import Preloaded

{-
Preloaded:

module Preloaded where

data Tree (A : Set) : Set where
  leaf : A → Tree A
  branch : A → Tree A → Tree A → Tree A

flipTree : {A : Set} → Tree A → Tree A
flipTree (leaf x) = leaf x
flipTree (branch x l r) = branch x (flipTree r) (flipTree l)
-}

flipTreeSym : {A : Set} → (t : Tree A) → t ≡ flipTree (flipTree t)
flipTreeSym (leaf x) = refl
flipTreeSym (branch x l r)
  rewrite sym (flipTreeSym l) | sym (flipTreeSym r)
  = refl
