Require Import Classical.

Theorem drinker : forall (A : Set) (r : A -> Prop) (e : A),
  exists x, (r x -> forall y, r y).
Proof.
  intros A r a.
  pose proof classic (exists x, ~ r x) as [[x H] | H].
  - exists x. intro Hx; easy.
  - assert (forall x, ~ ~ r x). apply not_ex_all_not; auto.
    exists a; intros. specialize H0 with y. apply NNPP in H0. assumption.
Qed.
