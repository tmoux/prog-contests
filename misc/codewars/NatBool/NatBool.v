Inductive three := C1 | C2 | C3.

Definition P (A : Type) := 
  forall (f : three -> A), exists a b, ~ a = b /\ f a = f b.

Lemma bool_P : P bool.
Proof.
  intros f.
  destruct (f C1) eqn:H1, (f C2) eqn:H2, (f C3) eqn:H3;
  solve [ 
    exists C1, C2; split; [discriminate | rewrite H1; rewrite H2; auto ] |
    exists C2, C3; split; [discriminate | rewrite H2; rewrite H3; auto ] |
    exists C1, C3; split; [discriminate | rewrite H1; rewrite H3; auto ] 
  ].
Qed.

Definition f : three -> nat := fun x => match x with
  | C1 => 0
  | C2 => 1
  | C3 => 3
  end.

Lemma not_bool_P : ~ P nat.
  unfold P. unfold not.
  intros.
  specialize H with f.
  destruct H as [a [b [H1 H2]]].
  destruct a, b; try apply H1; try discriminate; auto.
Qed.

Theorem is_nat_bool : (nat = bool) \/ (nat <> bool).
Proof.
  right. 
  intros eq.
  assert (H := bool_P).
  rewrite <- eq in H. apply (not_bool_P H).
Qed.
