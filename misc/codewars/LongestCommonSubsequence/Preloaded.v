Require Import Arith List Lia.
From Equations Require Import Equations.
Import ListNotations.

Inductive Subseq {A : Type} : list A -> list A -> Prop :=
| Subseq_nil : Subseq [] []
| Subseq_take : forall a xs ys, Subseq xs ys -> Subseq (a :: xs) (a :: ys)
| Subseq_drop : forall a xs ys, Subseq xs ys -> Subseq xs (a :: ys).

Definition IsLCS {A : Type} (zs xs ys : list A) : Prop :=
  Subseq zs xs /\ Subseq zs ys /\
  forall zs', Subseq zs' xs -> Subseq zs' ys -> length zs' <= length zs.

Equations lcs {A : Type} (eq_dec : forall x y : A, {x = y} + {x <> y})
          (l1 l2 : list A) : list A by wf (length l1 + length l2) lt :=
  lcs _ [] _ := [];
  lcs _ _ [] := [];
  lcs _ (x :: l1) (y :: l2) := 
    if eq_dec x y then x :: lcs eq_dec l1 l2 else
      let s1 := lcs eq_dec (x :: l1) l2 in
      let s2 := lcs eq_dec l1 (y :: l2) in
      if length s1 <? length s2 then s2 else s1.
Next Obligation. simpl; lia. Qed.
Next Obligation. simpl; lia. Qed.
