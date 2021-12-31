{-# OPTIONS --safe #-}
module PerfectSquare where

open import Data.Nat
open import Data.Nat.Properties
open import Relation.Binary.PropositionalEquality

open import Data.Nat.Solver using (module +-*-Solver)
open +-*-Solver using (solve; _:*_; _:+_; _:^_; con; _:=_)

expand : ∀ n -> (n + 1) ^ 2 ≡ n ^ 2 + 2 * n + 1
expand = solve 1 (λ x → (x :+ con 1) :^ 2 := x :^ 2 :+ con 2 :* x :+ con 1) refl


