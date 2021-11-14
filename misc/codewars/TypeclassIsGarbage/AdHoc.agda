{-# OPTIONS --safe #-}

module AdHoc where

open import Data.Char
open import Data.String hiding (length)
open import Data.List
open import Data.Integer as I
open import Data.Nat as N
open import Agda.Builtin.Nat using (_==_)
open import Data.Bool as B public
open import Relation.Nullary

record Eq {ℓ} (A : Set ℓ) : Set ℓ where
  field
    _===_ : A → A → Bool
    _=/=_ : A → A → Bool
    
open Eq {{...}} public


instance
  IntEq : Eq ℤ
  _===_ {{IntEq}} = eq 
   where
    eq : ℤ → ℤ → Bool
    eq x y with (x I.≟ y)
    ... | (yes p) = true
    ... | (no p) = false
  _=/=_ {{IntEq}} = λ x y → not (x === y)

  NatEq : Eq ℕ
  _===_ {{NatEq}} = Agda.Builtin.Nat._==_
  _=/=_ {{NatEq}} = λ x y → not (x === y)
  
  CharEq : Eq Char
  _===_ {{CharEq}} = Data.Char._==_
  _=/=_ {{CharEq}} = λ x y → not (x === y)
  
  BoolEq : Eq Bool
  _===_ {{BoolEq}} = eq 
    where
      eq : Bool → Bool → Bool
      eq false false = true
      eq true true = true
      eq _ _ = false
  _=/=_ {{BoolEq}} = λ x y → not (x === y)

  StringEq : Eq String
  _===_ {{StringEq}} = Data.String._==_
  _=/=_ {{StringEq}} = λ x y → not (x === y)
  
  ListEq : ∀ {A : Set} → {{eq : Eq A}} → Eq (List A)
  _===_ {{ListEq}} = λ { 
    [] [] → true ; 
    (x ∷ xs) (y ∷ ys) → x === y ∧ xs === ys;
    _ _ → false}
  _=/=_ {{ListEq}} = λ x y → not (x === y)
  

-- write something
-- _===_ : A → A → Bool
-- _=/=_ : A → A → Bool

