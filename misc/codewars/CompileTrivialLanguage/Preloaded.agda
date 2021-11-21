{-# OPTIONS --safe #-}
module Preloaded where

open import Data.Nat public
open import Data.List public

data Expr : Set where
  const : ℕ → Expr
  plus : Expr → Expr → Expr

eval-expr : Expr → ℕ
eval-expr (const n) = n
eval-expr (plus e1 e2) = eval-expr e1 + eval-expr e2

eval-expr-tail' : Expr → ℕ → ℕ
eval-expr-tail' (const n) acc = n + acc
eval-expr-tail' (plus e1 e2) acc = eval-expr-tail' e2 (eval-expr-tail' e1 acc)

eval-expr-tail : Expr → ℕ
eval-expr-tail e = eval-expr-tail' e 0

eval-expr-cont' : {A : Set} → Expr → (ℕ → A) → A
eval-expr-cont' (const n) k = k n
eval-expr-cont' (plus e1 e2) k = eval-expr-cont' e2 λ n2 →
                                 eval-expr-cont' e1 λ n1 → k (n1 + n2)

eval-expr-cont : Expr → ℕ
eval-expr-cont e = eval-expr-cont' e (λ n → n)

data Instr : Set where
  push : ℕ → Instr
  add : Instr

Prog = List Instr

Stack = List ℕ

run : Prog → Stack → Stack
run [] s = s
run (push n ∷ p) s = run p (n ∷ s)
run (add ∷ p) (a1 ∷ a2 ∷ s) = run p (a1 + a2 ∷ s)
run (add ∷ p) s = run p s

compile : Expr → Prog
compile (const n) = push n ∷ []
compile (plus e1 e2) = compile e1 ++ compile e2 ++ add ∷ []