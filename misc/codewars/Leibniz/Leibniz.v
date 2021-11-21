Section Leibniz.
Variables A : Type.
Variables a b c : A.
Definition leibniz (a b : A) := forall (P : A -> Prop), P a -> P b.

Lemma leibniz_reflexive : leibniz a a.
Proof. 
  unfold leibniz. 
  intros P Ha.
  assumption.
Qed.

Lemma leibniz_symmetric : leibniz a b -> leibniz b a.
Proof.
  unfold leibniz.
  intros H P Pb.
  specialize H with (fun z => P z -> P a).
  simpl in H.
  apply H.
  intros; assumption.
  assumption.
Qed.

Lemma leibniz_transitive : leibniz a b -> leibniz b c -> leibniz a c.
Proof.
  unfold leibniz.
  intros H1 H2 P Ha.
  apply H2. apply H1. assumption.
Qed.

Lemma leibniz_equiv_eq : leibniz a b <-> a = b.
Proof.
  unfold leibniz.
  split; intros H.
  specialize H with (fun x => a = x). simpl in H.
  apply H.
  reflexivity.
  
  intros P Ha.
  rewrite <- H. assumption.
Qed.

End Leibniz.
