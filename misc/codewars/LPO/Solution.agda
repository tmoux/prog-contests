{-# OPTIONS --safe #-}
module Solution where

open import Preloaded

open import Relation.Nullary
open import Relation.Binary.PropositionalEquality hiding ( [_] )
open import Data.Sum
open import Data.Product
open import Data.Bool
open import Data.Nat
open import Data.Empty

exists-neg : {A : Set} {P : A → Set} → (¬ ∃ (λ x → P x)) → (∀ (x : A) → ¬ P x)
exists-neg ¬ex_p x Px = ¬ex_p (x , Px)

not-true-is-false : {x : Bool} → ¬ (x ≡ true) → x ≡ false
not-true-is-false {false} = λ _ → refl
not-true-is-false {true} = λ x → ⊥-elim (x refl)

EM⇒LPO : EM → LPO
EM⇒LPO em f = Data.Sum.map₁ (λ ex m → not-true-is-false (exists-neg ex m)) (Data.Sum.swap (em (∃ (λ n → f n ≡ true))))

even-or-odd : (x : ℕ) → even x ≡ true ⊎ even x ≡ false
even-or-odd zero = inj₁ refl
even-or-odd (suc x) with (even x)
... | true = inj₂ refl
... | false = inj₁ refl

true-false-contra : {x : Bool} → x ≡ true → x ≡ false → ⊥
true-false-contra x-true x-false with trans (sym x-true) x-false
... | ()

even-is-not-odd : (x y : ℕ) → even x ≡ true → even y ≡ false → x ≢ y
even-is-not-odd x y even-x odd-y x≡y rewrite x≡y = ⊥-elim (true-false-contra even-x odd-y)

LPO⇒LLPO : LPO → LLPO
LPO⇒LLPO lpo f atmost-one-true = 
  [ (λ all-false → inj₁ λ n x → all-false n) , g ] (lpo f)
  where 
    g : (∃ (λ n → f n ≡ true)) → ((n : ℕ) → even n ≡ true → f n ≡ false) ⊎ ((n : ℕ) → even n ≡ false → f n ≡ false)
    g (x , fx-true) with (even-or-odd x)
    ... | inj₁ x-is-even = inj₂ λ y y-odd → [ (λ fx-false → ⊥-elim (true-false-contra fx-true fx-false)) , (λ x → x) ] (atmost-one-true x y (even-is-not-odd x y x-is-even y-odd))
    ... | inj₂ x-is-odd = inj₁ λ y y-even → [ (λ x → x) , (λ fx-false → ⊥-elim (true-false-contra fx-true fx-false) ) ] (atmost-one-true y x (even-is-not-odd y x y-even x-is-odd)) 
