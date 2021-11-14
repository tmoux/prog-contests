{-# OPTIONS --safe #-}
module Solution where

open import Relation.Nullary
open import Preloaded
open import Relation.Nullary.Negation
{- Preloaded:

module Preloaded where

open import Data.List public

data Suf {X : Set} : List X → List X → Set where
  sinit : ∀ l → Suf l l
  scons : ∀ x l l' → Suf l l' → Suf (x ∷ l) l'
-}

Suf-lem : ∀ {X} {x} {l1 l2 : List X} → Suf l1 (x ∷ l2) → Suf l1 l2
Suf-lem {X} {x} {.(x ∷ l2)} {l2} (sinit .(x ∷ l2)) = scons x l2 l2 (sinit l2)
Suf-lem {X} {x} {.(y ∷ l)} {l2} (scons y l .(x ∷ l2) suf) = scons y l l2 (Suf-lem suf)

less-is-not-more : ∀ {X} x (l : List X) → ¬ Suf l (x ∷ l)
less-is-not-more x (y ∷ l) (scons .y .l .(x ∷ y ∷ l) suf) = (less-is-not-more y l) (Suf-lem suf) 
