{-# OPTIONS --safe #-}
module Tests where

open import AdHoc
open import Relation.Binary.PropositionalEquality

open import Data.List

-- _ : (true === true) ≡ true
-- _ = refl

_ : (1 === 1) ≡ true
_ = refl

_ : (1 =/= 1) ≡ false
_ = refl

_ : ((1 ∷ 2 ∷ 3 ∷ []) === (1 ∷ 2 ∷ 3 ∷ [])) ≡ true
_ = refl
