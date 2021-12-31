{-# OPTIONS --safe #-}
module Uneval where

open import Agda.Builtin.Reflection

open import Relation.Nullary
open import Eval
{- Preloaded code are in the Eval module:

data Eval : Set where
  _!+_ : Eval → Eval → Eval
  _!*_ : Eval → Eval → Eval
  !lit : ℕ → Eval
  !zro : Eval
  !suc : Eval → Eval
-}

open import Data.Unit
open import Data.List using ([]; _∷_)
open import Data.Maybe using (Maybe; just; nothing; maybe′)
open import Agda.Builtin.Reflection renaming (bindTC to _>>=_)

-- ??? How can I prevent the evaluation of the argument ???
macro
  parseℕ : Term → Term → TC ⊤
  parseℕ t hole = do
    let eval = go t
    eval' ← quoteTC eval
    unify hole eval'
    where
      go : Term → Eval
      go (def (quote _+_) (arg i x ∷ arg j y ∷ [])) = (go x) !+ (go y)
      go (def (quote _*_) (arg i x ∷ arg j y ∷ [])) = (go x) !* (go y)
      go (lit (nat x)) = !lit x
      go (con (quote zero) []) = !zro
      go (con (quote suc) (arg i x ∷ [])) = !suc (go x)
      go _ = !zro


open import Relation.Binary.PropositionalEquality
_ : parseℕ 3 ≡ !lit 3
_ = refl

_ : !lit 233 ≡ parseℕ 233
_ = refl

_ : parseℕ zero ≡ !zro
_ = refl

_ : parseℕ (suc zero) ≡ !suc !zro
_ = refl

_ : parseℕ (suc (suc (suc zero))) ≡ !suc (!suc (!suc !zro))
_ = refl

_ : (!lit 2 !+ !lit 2) ≡ parseℕ (2 + 2)
_ = refl

_ : !lit 233 ≡ parseℕ 233
_ = refl
_ : (!lit 2 !+ !lit 2) ≡ parseℕ (2 + 2)
_ = refl
_ : (!lit 2 !* !lit 2) ≡ parseℕ (2 * 2)
_ = refl
_ : (!lit 2 !+ (!lit 2 !* !lit 2)) ≡ parseℕ (2 + (2 * 2))
_ = refl
_ : ((!lit 2 !+ (!lit 2 !* !suc (!lit 2))) !+ !zro) ≡ parseℕ (2 + (2 * suc 2) + zero)
_ = refl
