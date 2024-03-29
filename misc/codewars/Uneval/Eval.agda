{-# OPTIONS --safe #-}
module Eval where

open import Data.Nat public

data Eval : Set where
  _!+_ : Eval → Eval → Eval
  _!*_ : Eval → Eval → Eval
  !lit : ℕ → Eval
  !zro : Eval
  !suc : Eval → Eval
