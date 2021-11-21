{-# OPTIONS --safe #-}
module Solution where

open import Relation.Binary.PropositionalEquality
open import Data.Nat.Properties
open import Data.List.Properties
open import Preloaded

{- Preloaded:

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

-}

-- Task 1 - 1. Prove that eval-expr-tail is equivalent to eval-expr.

eval-expr-tail'-correct : ∀ e acc → eval-expr-tail' e acc ≡ acc + eval-expr e
eval-expr-tail'-correct (const x) acc rewrite (+-comm x acc) = refl
eval-expr-tail'-correct (plus e1 e2) acc 
  rewrite (eval-expr-tail'-correct e1 acc) 
        | (eval-expr-tail'-correct e2 (acc + eval-expr e1)) 
        | (+-assoc acc (eval-expr e1) (eval-expr e2)) = refl

eval-expr-tail-correct : ∀ e → eval-expr-tail e ≡ eval-expr e
eval-expr-tail-correct e = eval-expr-tail'-correct e 0

-- Task 1 - 2. Prove that eval-expr-cont is equivalent to eval-expr.

eval-expr-cont-correct' : {A : Set} → (e : Expr) → (k : ℕ → A) → eval-expr-cont' e k ≡ k (eval-expr e)
eval-expr-cont-correct' (const x) k = refl
eval-expr-cont-correct' (plus e1 e2) k 
  rewrite eval-expr-cont-correct' e2 (λ n2 → eval-expr-cont' e1 (λ n1 → k (n1 + n2))) 
  | eval-expr-cont-correct' e1 (λ n1 → k (n1 + eval-expr e2)) = refl

eval-expr-cont-correct : ∀ e → eval-expr-cont e ≡ eval-expr e
eval-expr-cont-correct e = eval-expr-cont-correct' e (λ n → n) 

-- Task 2. Prove that you get the expected result when you compile and run the program.

compile-lemma : ∀ e b st → run (compile e ++ b) st ≡ run b (eval-expr e ∷ st)
compile-lemma (const x) b st = refl
compile-lemma (plus e₁ e₂) b st 
  rewrite ++-assoc (compile e₁) (compile e₂ ++ add ∷ []) b 
  | compile-lemma e₁ ((compile e₂ ++ add ∷ []) ++ b) st 
  | ++-assoc (compile e₂) (add ∷ []) b 
  | compile-lemma e₂ (add ∷ b) (eval-expr e₁ ∷ st) 
  | +-comm (eval-expr e₂) (eval-expr e₁) = refl

compile-correct : ∀ e → run (compile e) [] ≡ eval-expr e ∷ []
compile-correct e 
  rewrite (sym (++-identityʳ (compile e))) = compile-lemma e [] [] 
