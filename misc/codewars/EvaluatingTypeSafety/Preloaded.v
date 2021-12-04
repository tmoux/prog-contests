Inductive tm : Type :=
  | zro : tm
  | scc : tm -> tm
  | pls : tm -> tm -> tm
  | nul : tm
  | cns : tm -> tm -> tm
  | len : tm -> tm
  | idx : tm -> tm -> tm
  | stn : tm -> tm.

Inductive nvalue : tm -> Prop :=
  | nv_zro : nvalue zro
  | nv_scc : forall v1, nvalue v1 -> nvalue (scc v1).

Inductive lvalue : tm -> Prop :=
  | lv_nul : lvalue nul
  | lv_cns : forall v1 v2,
      nvalue v1 -> lvalue v2 -> lvalue (cns v1 v2).

Definition value (t : tm) := nvalue t \/ lvalue t.

Reserved Notation "t1 '-->' t2" (at level 40).

Inductive step : tm -> tm -> Prop :=
  | ST_Scc : forall t1 t1',
      t1 --> t1' ->
      scc t1 --> scc t1'
  | ST_PlsZro : forall v1,
      nvalue v1 ->
      pls zro v1 --> v1
  | ST_PlsScc : forall v1 v2,
      nvalue v1 ->
      nvalue v2 ->
      pls (scc v1) v2 --> scc (pls v1 v2)
  | ST_Pls2 : forall v1 t2 t2',
      nvalue v1 ->
      t2 --> t2' ->
      pls v1 t2 --> pls v1 t2'
  | ST_Pls1 : forall t1 t1' t2,
      t1 --> t1' ->
      pls t1 t2 --> pls t1' t2
  | ST_Cns2 : forall v1 t2 t2',
      nvalue v1 ->
      t2 --> t2' ->
      cns v1 t2 --> cns v1 t2'
  | ST_Cns1 : forall t1 t1' t2,
      t1 --> t1' ->
      cns t1 t2 --> cns t1' t2
  | ST_LenNul :
      len nul --> zro
  | ST_LenCns : forall v1 v2,
      nvalue v1 ->
      lvalue v2 ->
      len (cns v1 v2) --> scc (len v2)
  | ST_Len : forall t1 t1',
      t1 --> t1' ->
      len t1 --> len t1'
  | ST_IdxZro : forall v1 v2,
      nvalue v1 ->
      lvalue v2 ->
      idx zro (cns v1 v2) --> v1
  | ST_IdxScc : forall v1 v2 v3,
      nvalue v1 ->
      nvalue v2 ->
      lvalue v3 ->
      idx (scc v1) (cns v2 v3) --> idx v1 v3
  | ST_Idx2 : forall v1 t2 t2',
      nvalue v1 ->
      t2 --> t2' ->
      idx v1 t2 --> idx v1 t2'
  | ST_Idx1 : forall t1 t1' t2,
      t1 --> t1' ->
      idx t1 t2 --> idx t1' t2
  | ST_StnNval : forall v1,
      nvalue v1 ->
      stn v1 --> cns v1 nul
  | ST_Stn : forall t1 t1',
      t1 --> t1' ->
      stn t1 --> stn t1'

where "t1 '-->' t2" := (step t1 t2).

Definition relation (X : Type) := X -> X -> Prop.

Definition deterministic {X : Type} (R : relation X) :=
  forall x y1 y2 : X, R x y1 -> R x y2 -> y1 = y2.

Inductive ty : Type :=
  | Nat : ty
  | List : ty.

Reserved Notation "'|-' t '\in' T" (at level 40).

Inductive has_type : tm -> ty -> Prop :=
  | T_Zro :
      |- zro \in Nat
  | T_Scc : forall t1,
      |- t1 \in Nat ->
      |- scc t1 \in Nat
  | T_Pls : forall t1 t2,
      |- t1 \in Nat ->
      |- t2 \in Nat ->
      |- pls t1 t2 \in Nat
  | T_Nul :
      |- nul \in List
  | T_Cns : forall t1 t2,
      |- t1 \in Nat ->
      |- t2 \in List ->
      |- cns t1 t2 \in List
  | T_Len : forall t1,
      |- t1 \in List ->
      |- len t1 \in Nat
  | T_Idx : forall t1 t2,
      |- t1 \in Nat ->
      |- t2 \in List ->
      |- idx t1 t2 \in Nat
  | T_Stn : forall t1,
      |- t1 \in Nat ->
      |- stn t1 \in List

where "'|-' t '\in' T" := (has_type t T).

Definition progress := forall t T,
  |- t \in T ->
  value t \/ exists t', t --> t'.

Definition preservation := forall t t' T,
  |- t \in T ->
  t --> t' ->
  |- t' \in T.

Inductive multi {X : Type} (R : relation X) : relation X :=
  | multi_refl : forall (x : X), multi R x x
  | multi_step : forall (x y z : X),
                    R x y ->
                    multi R y z ->
                    multi R x z.

Definition multistep := (multi step).
Notation "t1 '-->*' t2" := (multistep t1 t2) (at level 40).

Definition normal_form {X : Type} (R : relation X) (t : X) : Prop :=
  ~ exists t', R t t'.

Notation step_normal_form := (normal_form step).

Definition stuck (t : tm) : Prop :=
  step_normal_form t /\ ~ value t.

Definition soundness := forall t t' T,
  |- t \in T ->
  t -->* t' ->
  ~ stuck t'.
