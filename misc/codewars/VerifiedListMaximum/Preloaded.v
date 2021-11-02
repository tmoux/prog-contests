Require Import Coq.Lists.List.
Import ListNotations.
Require Import Coq.ZArith.BinInt.
Open Scope Z_scope.

Definition list_max_Z : list Z -> Z := fold_right Z.max 0.
