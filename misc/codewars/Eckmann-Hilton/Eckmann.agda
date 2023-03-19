module Eckmann where

open import Relation.Binary.PropositionalEquality
open Relation.Binary.PropositionalEquality.≡-Reasoning

module _
  (A : Set)
  (_×_ _·_ : A → A → A) 
  (1a 1b : A)
  (1a-unitl : ∀ {x : A} → 1a × x ≡ x)
  (1a-unitr : ∀ {x : A} → x × 1a ≡ x)
  (1b-unitl : ∀ {x : A} → 1b · x ≡ x)
  (1b-unitr : ∀ {x : A} → x · 1b ≡ x)
  (dist : ∀ {a b c d : A} → (a · b) × (c · d) ≡ (a × c) · (b × d))
  where

  units-same : 1a ≡ 1b
  units-same =
    begin
      1a
    ≡⟨ sym (1b-unitr) ⟩
      1a · 1b
    ≡⟨ sym (1a-unitr) ⟩
      (1a · 1b) × 1a
    ≡⟨ cong (λ z → (1a · 1b) × z) (sym 1b-unitl) ⟩
      (1a · 1b) × (1b · 1a)
    ≡⟨ dist ⟩
      (1a × 1b) · (1b × 1a)
    ≡⟨ cong (λ z → z · (1b × 1a)) 1a-unitl ⟩
      1b · (1b × 1a)
    ≡⟨ cong (λ z → 1b · z) 1a-unitr ⟩
      1b · 1b
    ≡⟨ 1b-unitl ⟩
      1b
    ∎

  ops-same : ∀ (x y : A) → x × y ≡ x · y
  ops-same x y = 
    begin
      x × y
    ≡⟨ cong (λ z → z × y) (sym 1b-unitr) ⟩
      (x · 1b) × y
    ≡⟨ cong (λ z → (x · 1b) × z) (sym 1b-unitl) ⟩
      (x · 1b) × (1b · y)
    ≡⟨ dist ⟩
      (x × 1b) · (1b × y)
    ≡⟨ cong (λ z → (x × z) · (1b × y)) (sym units-same) ⟩
      (x × 1a) · (1b × y)
    ≡⟨ cong (λ z → (x × 1a) · (z × y)) (sym units-same) ⟩
      (x × 1a) · (1a × y)
    ≡⟨ cong (λ z → z · (1a × y)) 1a-unitr ⟩
      x · (1a × y)
    ≡⟨ cong (λ z → x · z) 1a-unitl ⟩
      x · y
    ∎

  ops-commute : ∀ (x y : A) → (x × y ≡ y × x)
  ops-commute x y = 
    begin
      x × y
    ≡⟨ cong (λ z → z × y) (sym 1b-unitl) ⟩
      (1b · x) × y
    ≡⟨ cong (λ z → (1b · x) × z) (sym 1b-unitr) ⟩
      (1b · x) × (y · 1b)
    ≡⟨ dist ⟩ 
      (1b × y) · (x × 1b)
    ≡⟨ cong (λ z → (z × y) · (x × 1b)) (sym units-same) ⟩ 
      (1a × y) · (x × 1b)
    ≡⟨ cong (λ z → (1a × y) · (x × z)) (sym units-same) ⟩ 
      (1a × y) · (x × 1a)
    ≡⟨ cong (λ z → z · (x × 1a)) 1a-unitl ⟩ 
      y · (x × 1a)
    ≡⟨ cong (λ z → y · z) 1a-unitr ⟩ 
      y · x
    ≡⟨ sym (ops-same y x) ⟩ 
      y × x
    ∎  

  dist-× : ∀ (a b c d : A) → (a × b) × (c × d) ≡ (a × c) × (b × d)
  dist-× a b c d = 
    begin
      (a × b) × (c × d)
    ≡⟨ ops-same (a × b) (c × d) ⟩ 
      (a × b) · (c × d)
    ≡⟨ sym dist ⟩ 
      (a · c) × (b · d)
    ≡⟨ cong (λ z → z × (b · d)) (sym (ops-same _ _)) ⟩ 
      (a × c) × (b · d)
    ≡⟨ cong (λ z → (a × c) × z) (sym (ops-same _ _)) ⟩ 
      (a × c) × (b × d)
    ∎

  ops-assoc : ∀ (x y z : A) → (x × y) × z ≡ x × (y × z)
  ops-assoc x y z = 
    begin
      (x × y) × z
    ≡⟨ cong (λ w → (x × y) × w) (sym 1a-unitl) ⟩ 
      (x × y) × (1a × z)
    ≡⟨ dist-× _ _ _ _ ⟩ 
      (x × 1a) × (y × z)
    ≡⟨ cong (λ w → w × (y × z)) 1a-unitr ⟩ 
      x × (y × z)
    ∎