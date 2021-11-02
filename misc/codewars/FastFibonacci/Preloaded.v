Require Import Arith.
Import Nat.

Fixpoint fib (n : nat) : nat :=
  match n with
  | 0 => 0
  | 1 => 1
  | S (S n as n') => fib n' + fib n
  end.

Fixpoint fib2 t n : nat * nat :=
  match t, n with
  | 0, _ => (0, 1)
  | S t, 0 => (0, 1)
  | S t, _ =>
    let (a, b) := fib2 t (n / 2) in
    let c := a * (2 * b - a) in
    let d := a * a + b * b in
    if even n then (c, d) else (d, c + d)
  end.

Definition fib_fast n := fst (fib2 n n).
