{-# OPTIONS --safe #-}
open import Data.List public

data Suf {X : Set} : List X → List X → Set where
  sinit : ∀ l → Suf l l
  scons : ∀ x l l' → Suf l l' → Suf (x ∷ l) l'
