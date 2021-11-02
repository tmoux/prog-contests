Require Import Coq.Lists.List.
Require Import Coq.ZArith.BinInt.
Require Import Preloaded.

Lemma list_max_Z_spec : forall l,
  let max_val := list_max_Z l in
  Forall (fun x => x <= max_val) l /\
  (In max_val l \/ max_val = 0).
  
  
Proof. 
  intros.
  induction l; simpl in max_val.
  - split. constructor. right. auto.
  - simpl in IHl. split.
    + constructor. apply Z.le_max_l. destruct IHl. 
      apply Forall_impl with (P := fun x => x <= list_max_Z l).
      intros. assert (list_max_Z l <= max_val). apply Z.le_max_r. apply Z.le_trans with (list_max_Z l); assumption. 
      assumption.
    + destruct IHl. pose proof (Z.max_spec a (list_max_Z l)). destruct H1 as [[H1 H2] | [H1 H2]].
      assert (max_val = list_max_Z l). auto.
      rewrite H3.
      destruct H0. left. simpl. right. assumption.
      right. assumption.
      
      assert (max_val = a). auto. rewrite H3. left. constructor. auto.
Qed.
