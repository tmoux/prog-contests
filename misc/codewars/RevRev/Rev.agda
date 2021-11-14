{-# OPTIONS --safe #-}

module Rev where

open import Data.List


rev : ∀ {ℓ} {A : Set ℓ} → List A → List A
rev [] = []
rev (x ∷ xs) = rev xs ++ x ∷ [] 
