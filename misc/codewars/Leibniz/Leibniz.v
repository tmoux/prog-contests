Definition leibniz {A : Type} (a b : A) := forall (P : A -> Prop), P a -> P b.

Lemma leibniz_symmetric {A : Type} : forall (a b : A), leibniz a b -> leibniz b a.
Proof.
  unfold leibniz.
  intros a b H P Pb.
  specialize H with (fun z => P z -> P a).
  simpl in H.
  apply H.
  intros; assumption.
  assumption.
Qed.

Lemma leibniz_reflexive {A : Type} : forall (a : A), leibniz a a.
Proof. 
  unfold leibniz. 
  intros a P Ha.
  assumption.
Qed.

Lemma leibniz_transitive {A : Type} : forall (a b c : A), leibniz a b -> leibniz b c -> leibniz a c.
Proof.
  unfold leibniz.
  intros a b c H1 H2 P Ha.
  apply H2. apply H1. assumption.
Qed.

Lemma leibniz_equiv_eq {A : Type} : forall (a b : A), leibniz a b <-> a = b.
Proof.
  unfold leibniz.
  split; intros H.
  specialize H with (fun x => a = x). simpl in H.
  apply H.
  reflexivity.
  
  intros P Ha.
  rewrite <- H. 
  assumption.
Qed.
