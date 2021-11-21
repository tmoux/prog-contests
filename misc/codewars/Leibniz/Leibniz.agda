module Leibniz where

-- Meh this is too easy, can easily be C-a'd.
open import Relation.Binary.PropositionalEquality

_≐_ : ∀ {A : Set} (a b : A) → Set₁
_≐_ {A} a b = ∀ (P : A → Set) → P a → P b

-- Leibniz equality is an equivalence relation.
≐-reflexive : ∀ {A : Set} (a : A) → a ≐ a
≐-reflexive a = λ P z → z

≐-symmetric : ∀ {A : Set} (a b : A) → a ≐ b → b ≐ a
≐-symmetric a b a≐b = λ P → a≐b (λ z → (x : P z) → P a) (λ x → x)

≐-transitive : ∀ {A : Set} (a b c : A) → a ≐ b → b ≐ c → a ≐ c
≐-transitive a b c a≐b b≐c = λ P z → b≐c P (a≐b P z)


-- Leibniz equality is equivalent to propositional equality.

≡→≐ : ∀ {A : Set} (a b : A) → a ≡ b → a ≐ b
≡→≐ a b a≡b rewrite a≡b = λ P x → x

≐→≡ : ∀ {A : Set} (a b : A) → a ≐ b → a ≡ b
≐→≡ a b a≐b = a≐b (_≡_ a) refl
