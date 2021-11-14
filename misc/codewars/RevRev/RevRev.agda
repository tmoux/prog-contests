{-# OPTIONS --safe #-}
module RevRev where

open import Relation.Binary.PropositionalEquality
open import Data.List
open import Rev

{-
What you've just imported:

-- With this definition, Agda deduces better
rev : ∀ {ℓ} {A : Set ℓ} → List A → List A
rev [] = []
rev (x ∷ xs) = rev xs ++ x ∷ [] 
-}

rev-tail : ∀ {ℓ} {A : Set ℓ} (xs : List A) → ∀ (y : A) → rev (xs ++ y ∷ []) ≡ y ∷ rev xs
rev-tail [] y = refl
rev-tail (x ∷ xs) y 
  rewrite rev-tail xs y = refl

revrevid : ∀ {ℓ} {A : Set ℓ} (a : List A) → rev (rev a) ≡ a
revrevid [] = refl
revrevid (x ∷ l) 
  rewrite rev-tail (rev l) x | revrevid l = refl

