Require Import Preloaded.
Require Import Lia Arith List.
Import ListNotations.

Check lcs_equation_1. 
Check lcs_equation_2. 
Check lcs_equation_3. 

Hint Constructors Subseq : core.

Lemma subseq_drop_head {A : Type} (eq_dec : forall x y : A, {x = y} + {x <> y}) : forall (x : A) (xs ys : list A), Subseq (x :: xs) ys -> Subseq xs ys.
Proof.
  intros.
  generalize dependent xs.
  induction ys; intros.
  - inversion H.
  - inversion H; subst.
    + apply Subseq_drop. assumption.
    + apply Subseq_drop. apply IHys. auto.
Qed.

Lemma subseq_empty {A : Type} : forall (xs : list A), Subseq [] xs.
Proof.
  intros; induction xs; auto.
Qed.

Lemma lcs_subseq_xs {A : Type} (eq_dec : forall x y : A, {x = y} + {x <> y}) xs ys : Subseq (lcs eq_dec xs ys) xs.
Proof.
  generalize dependent ys. induction xs; intros.
  rewrite lcs_equation_1; apply Subseq_nil.

  induction ys; intros.
  - rewrite lcs_equation_2; apply subseq_empty.
  - rename a into x; rename a0 into y.
    rewrite lcs_equation_3.
    destruct (eq_dec x y).
    + apply Subseq_take. apply IHxs.
    + simpl. destruct (length (lcs eq_dec (x :: xs) ys) <? length (lcs eq_dec xs (y :: ys))).
      apply Subseq_drop. apply IHxs.
      apply IHys.
Qed.

Lemma lcs_subseq_ys {A : Type} (eq_dec : forall x y : A, {x = y} + {x <> y}) xs ys : Subseq (lcs eq_dec xs ys) ys.
Proof.
  generalize dependent ys. induction xs; intros.
  rewrite lcs_equation_1; apply subseq_empty.

  induction ys; intros.
  - rewrite lcs_equation_2; apply Subseq_nil.
  - rename a into x; rename a0 into y.
    rewrite lcs_equation_3.
    destruct (eq_dec x y).
    + subst. apply Subseq_take. apply IHxs.
    + simpl. destruct (length (lcs eq_dec (x :: xs) ys) <? length (lcs eq_dec xs (y :: ys))).
      apply IHxs.
      apply Subseq_drop. apply IHys.
Qed.

Definition l1 := [1; 2; 5; 7; 9].
Definition l2 := [1; 2; 6; 8; 9].
Compute (lcs Nat.eq_dec l1 l2).
Check (lcs_subseq_ys Nat.eq_dec l1 l2).


Theorem lcs_correct {A : Type} (eq_dec : forall x y : A, {x = y} + {x <> y}) xs ys :
  IsLCS (lcs eq_dec xs ys) xs ys.
Proof. 
  split.
  apply lcs_subseq_xs.
  split.
  apply lcs_subseq_ys.
  
  intros zs Hzx Hzy.
  generalize dependent zs.
  generalize dependent ys. induction xs; intros.
  inversion Hzx; subst. simpl; lia. 
  
  rename a into x.
  generalize dependent zs. 
  induction ys; intros.
  inversion Hzy; subst. simpl; lia.
  rename a into y.
  rewrite lcs_equation_3. destruct (eq_dec x y).
  - (* What if heads of xs and ys are the same? 
       Then 
    *)
    subst. simpl. 
    destruct zs as [|z zs]. simpl. lia.
    inversion Hzx; subst.
    inversion Hzy; subst.
    + simpl. pose proof (IHxs ys zs H0 H1). lia.
    + simpl. apply (subseq_drop_head eq_dec) in H2. pose proof (IHxs ys zs H0 H2). lia. 
    + simpl. apply (subseq_drop_head eq_dec) in H1. 
      inversion Hzy; subst. pose proof (IHxs ys zs H1 H0). lia. apply (subseq_drop_head eq_dec) in H2. pose proof (IHxs ys zs H1 H2). lia.
  - (* What if heads of xs and ys are not the same? 
    *)
    simpl. destruct (length (lcs eq_dec (x :: xs) ys) <? length (lcs eq_dec xs (y :: ys))) eqn:?.
    + destruct zs as [|z zs]. { simpl; lia. }
      inversion Hzx; subst. 
      apply Nat.ltb_lt in Heqb.
      assert (length (x :: zs) <= length (lcs eq_dec (x:: xs) ys)). { specialize IHys with (x :: zs). apply IHys; auto. inversion Hzy; subst. exfalso; auto. auto. } lia.
      specialize IHxs with (y :: ys) (z :: zs). apply IHxs; auto.
    + destruct zs as [|z zs]. { simpl; lia. }
      inversion Hzy; subst.
      apply Nat.ltb_ge in Heqb.
      assert (length (y :: zs) <= length (lcs eq_dec xs (y :: ys))). { specialize IHxs with (y :: ys) (y :: zs). inversion Hzx; subst. exfalso; auto. apply IHxs; auto. } lia.
      pose proof (IHys (z :: zs) Hzx H1). assumption.
Qed.
            
  
  
  

  

