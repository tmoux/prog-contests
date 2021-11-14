{-# OPTIONS --safe #-}

open import Level
open import Axiom.ExcludedMiddle

module DrinkerParadox (em : ∀ {ℓ : Level} → ExcludedMiddle ℓ) where

open import Data.Product
open import Relation.Unary

paradox : ∀ {ℓ : Level} {A : Set ℓ} {r : Pred A ℓ} →
  (e : A) →
  ∃[ x ] (r x -> ∀ {y : A} -> r y)
paradox = {!!}
--paradox {ℓ} {A} {r} e with 
--... | _ = ?
