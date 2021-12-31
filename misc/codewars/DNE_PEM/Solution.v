Definition axiom_pem := forall (P : Prop), P \/ ~P.

Definition axiom_dne := forall (P : Prop), ~ ~P -> P.

Theorem from : axiom_dne -> axiom_pem.
Proof.
  unfold axiom_dne, axiom_pem.
  intros H P.
  apply H.
  intuition.
Qed.
  
Theorem to : axiom_pem -> axiom_dne.
Proof.
  unfold axiom_pem, axiom_dne.
  intros H P.
  destruct (H P); intuition.
Qed.
