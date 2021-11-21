{-# OPTIONS --cubical #-}

module CubicalTest where

open import Cubical.Core.Everything

_ : I
_ = i0


andNot : I → I → I
andNot i j = ~ (i ∧ j)

andNot' : I → I → I
andNot' i j = ~ i ∨ ~ j


myImagination
  : (A : Set)
  → (a b : A)
  → Set
myImagination = Path

constantPathLam : (A : Set) → (a : A) → Path A a a
constantPathLam A a i = a
-- i i0 = a,
-- i i1 = a

constantPathLam` : (A : Set) → (a : A) → a ≡ a
constantPathLam` A a i = a


import Cubical.Foundations.Prelude as Prelude
_ : {A : Set} {a : A} → a ≡ a
_ = Prelude.refl

invert : (A : Set) (a b : A) (p : a ≡ b) → b ≡ a
invert    A         a b       p = λ i → p (~ i)

congruence
  : {A B : Set}
  → (f : A → B)
  → {x y : A}
  → (p : x ≡ y)
  → f x ≡ f y
congruence f p = λ i → f (p i)

functionExtensionality
  : {A B : Set}
  → {f g : A → B}
  → (p : ∀ a → f a ≡ g a)
  → f ≡ g
functionExtensionality p = λ i a → p a i
