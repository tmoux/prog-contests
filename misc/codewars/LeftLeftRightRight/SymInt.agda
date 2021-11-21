{-# OPTIONS --cubical --safe #-}
module SymInt where

open import Cubical.Core.Everything
open import Cubical.HITs.HitInt renaming (_+ℤ_ to _+_; ℤ to Z)

+-i-zero : ∀ a i → posneg i + a ≡ a
+-i-zero a i = ?
