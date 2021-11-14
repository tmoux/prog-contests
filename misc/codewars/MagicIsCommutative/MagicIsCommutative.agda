{-# OPTIONS --safe #-}
module MagicIsCommutative where

open import Relation.Binary.PropositionalEquality using (_≡_; sym; cong)
open Relation.Binary.PropositionalEquality.≡-Reasoning


record IsMagical {A : Set} (_∙_ : A → A → A) : Set where
  field
    left         : ∀ x y → (x ∙ y) ∙ y  ≡  x
    right        : ∀ x y → y ∙ (y ∙ x)  ≡  x

record IsCommuntative {A : Set} (_∙_ : A → A → A) : Set where
  field
    comm         : ∀ x y → x ∙ y  ≡ y ∙ x

open IsMagical
open IsCommuntative

magic-is-commutative : {A : Set} (_∙_ : A → A → A) → IsMagical _∙_ → IsCommuntative _∙_
magic-is-commutative _∙_ magic = record { comm = com }
  where  com : _
         com x y = begin
           x ∙ y ≡⟨ cong (λ z → x ∙ z) (sym (left magic y (y ∙ x))) ⟩
           x ∙ ((y ∙ (y ∙ x)) ∙ (y ∙ x)) ≡⟨ cong (λ z → x ∙ (z ∙ (y ∙ x))) (right magic x y) ⟩ 
           x ∙ (x ∙ (y ∙ x)) ≡⟨ right magic (y ∙ x) x ⟩ 
           y ∙ x ∎
