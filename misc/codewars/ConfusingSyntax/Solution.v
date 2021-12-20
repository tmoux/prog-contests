Require Import Lia.

Theorem exists_unique_le : exists! n m : nat, m <= n.
Proof. 
  exists 0. split.
  exists 0. split. auto.
  intros. inversion H; auto.
  intros. destruct H. unfold unique in H. destruct H.
  destruct x'. auto. 
  assert (x = 0). { apply H0. lia. }
  assert (x = 1). { apply H0. lia. }
  subst. discriminate.
Qed.
