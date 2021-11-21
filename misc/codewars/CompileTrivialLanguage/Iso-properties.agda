{-# OPTIONS --safe #-}
module Iso-properties where

open import Iso
open _⇔_

-- Task 0 : Example of _⇔_ in finite sets
-- Task 0-1. Find a bijection between Bool and Bit. (provided for you as an example)
data Bool : Set where
  true false : Bool
  
data Bit : Set where
  0b 1b : Bit

Bool→Bit : Bool → Bit
Bool→Bit false = 0b
Bool→Bit true = 1b

Bit→Bool : Bit → Bool
Bit→Bool 0b = false
Bit→Bool 1b = true

Bool→Bit→Bool : ∀ (b : Bool) → Bit→Bool (Bool→Bit b) ≡ b
Bool→Bit→Bool true = refl
Bool→Bit→Bool false = refl

Bit→Bool→Bit : ∀ (b : Bit) → Bool→Bit (Bit→Bool b) ≡ b
Bit→Bool→Bit 0b = refl
Bit→Bool→Bit 1b = refl

Bool⇔Bit : Bool ⇔ Bit
Bool⇔Bit = Bijection Bool→Bit Bit→Bool Bool→Bit→Bool Bit→Bool→Bit

--------------------------------------------------------------------
-- Task 1 : General properties of ⇔
-- Task 1-1. Prove that any set has the same cardinality as itself.
⇔-refl : ∀ {A : Set} → A ⇔ A
⇔-refl = Bijection (λ z → z) (λ z → z) (λ a → refl) (λ b → refl)

-- Task 1-2. Prove that _⇔_ relation is symmetric.
⇔-sym : ∀ {A B : Set} → A ⇔ B → B ⇔ A
⇔-sym (Bijection A→B B→A A→B→A B→A→B) = Bijection B→A A→B B→A→B A→B→A

-- Task 1-3. Prove that _⇔_ relation is transitive.
⇔-trans : ∀ {A B C : Set} → A ⇔ B → B ⇔ C → A ⇔ C
⇔-trans {A} {B} {C} (Bijection A→B B→A A→B→A B→A→B) (Bijection B→C C→B B→C→B C→B→C) = Bijection (λ z → B→C (A→B z)) (λ z → B→A (C→B z)) A→C→A C→A→C
  where 
    A→C→A : (a : A) → B→A (C→B (B→C (A→B a))) ≡ a
    A→C→A a rewrite (B→C→B (A→B a)) | (A→B→A a) = refl
    
    C→A→C : (c : C) → B→C (A→B (B→A (C→B c))) ≡ c
    C→A→C c rewrite (B→A→B (C→B c)) | (C→B→C c) = refl


-- Task 1-4. Prove the following statement:
--   Given two functions A→B and B→A, if A→B→A is satisfied and B→A is injective, A ⇔ B.
bijection-alt :
  ∀ {A B : Set} →
  (A→B : A → B) →
  (B→A : B → A) →
  (∀ a → B→A (A→B a) ≡ a) →
  (∀ b b' → B→A b ≡ B→A b' → b ≡ b') →
  A ⇔ B
bijection-alt A→B B→A A→B→A B→A-inj = Bijection A→B B→A A→B→A λ b → B→A-inj (A→B (B→A b)) b (A→B→A (B→A b))

--------------------------------------------------------------------
-- Task 2 : ⇔-relations between ℕ and various supersets of ℕ

-- ℕ+1 : A set having one more element than ℕ.
{- Preloaded code
data ℕ+1 : Set where
  null : ℕ+1
  nat : ℕ → ℕ+1
-}

-- Task 2-1. Prove that ℕ has the same cardinality as ℕ+1.
ℕ⇔ℕ+1 : ℕ ⇔ ℕ+1
ℕ⇔ℕ+1 = Bijection 
  (λ { zero → null ; (suc x) → nat x}) 
  (λ { null → 0 ; (nat x) → suc x}) 
  (λ { zero → refl ; (suc a) → refl}) 
  (λ { null → refl ; (nat x) → refl})

-- ℕ+ℕ : A set having size(ℕ) more elements than ℕ.
{- Preloaded code
data ℕ+ℕ : Set where
  left : ℕ → ℕ+ℕ
  right : ℕ → ℕ+ℕ
-}

-- Task 2-2. Prove that ℕ has the same cardinality as ℕ+ℕ.

suc-inj : ℕ+ℕ → ℕ+ℕ
suc-inj (left x) = left (suc x)
suc-inj (right x) = right (suc x)

inject : ℕ → ℕ+ℕ
inject zero = left zero
inject (suc zero) = right zero
inject (suc (suc x)) = suc-inj (inject x)

inject-inv : ℕ+ℕ → ℕ
inject-inv (left zero) = zero
inject-inv (left (suc x)) = suc (suc (inject-inv (left x)))
inject-inv (right zero) = suc zero
inject-inv (right (suc x)) = suc (suc (inject-inv (right x)))

inject-inv-suc : ∀ x → inject-inv (suc-inj x) ≡ suc (suc (inject-inv x))
inject-inv-suc (left x) = refl
inject-inv-suc (right x) = refl

inverse-1 : (a : ℕ) → inject-inv (inject a) ≡ a
inverse-1 zero = refl
inverse-1 (suc zero) = refl
inverse-1 (suc (suc x)) rewrite inject-inv-suc (inject x) | inverse-1 x = refl

inverse-2 : (a : ℕ+ℕ) → inject (inject-inv a) ≡ a
inverse-2 (left zero) = refl
inverse-2 (left (suc x)) rewrite inverse-2 (left x) = refl
inverse-2 (right zero) = refl
inverse-2 (right (suc x)) rewrite inverse-2 (right x) = refl

ℕ⇔ℕ+ℕ : ℕ ⇔ ℕ+ℕ
ℕ⇔ℕ+ℕ = Bijection 
  inject 
  inject-inv 
  inverse-1 
  inverse-2
