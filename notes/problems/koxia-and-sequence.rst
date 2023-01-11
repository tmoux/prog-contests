Problem Statement
=================

Test: :math:`\qed`. We are given integers :math:`1 \leq n < 2^{40}`,
:math:`0 \leq x < 2^{60}`, and :math:`0 \leq y < 2^{20}`. An array
:math:`A` of :math:`n` non-negative integers is **good** if
:math:`a_1 + a_2 + \dots + a_n = x` and
:math:`a_1 | a_2 | \dots | a_n = y`. We are asked to compute the bitwise
xor of all elements of all good arrays.

Formally, let the **score** of an array be
:math:`a_1 \oplus a_2 \oplus \dots \oplus a_n`. We want to compute the
**total score** (bitwise xor) of the scores of all good arrays.

High-Level Overview
===================

This can seem like an intimidating problem. One way to get started is to
write a brute force and see if there are any patterns in small cases.
Alternatively, the fact that we are dealing with xor instead of addition
or multiplication indicates that we can utilize some very nice symmetric
properties about xor. Here’s a simple observation we can make that
illustrates this point:

If :math:`n` is even, the total score is :math:`0`.

First note that in a palindrome of even length :math:`n`, each element
appears an even number of times, so its score is :math:`0`, and it does
not contribute to the total. Thus let’s only consider non-palindromic
good arrays. For any good array :math:`A`, consider its reverse
:math:`A'`, which is also a good array. We can compute the total score
by pairing up arrays and their reverse (e.g.,
:math:`(\mathop{\mathrm{score}}(A) \oplus \mathop{\mathrm{score}}(A')) \oplus (\mathop{\mathrm{score}}(B) \oplus \mathop{\mathrm{score}}(B')) \oplus \dots`).
For each pair :math:`A` and :math:`A'`, the two arrays contain the same
elements, so
:math:`\mathop{\mathrm{score}}(A) \oplus \mathop{\mathrm{score}}(A') = 0`.
Thus the total score is also :math:`0`.

This simple proof illustrates an important concept that we will use
later: if we have a set :math:`S` and an involution :math:`f : S \to S`
(i.e., :math:`f(f(s)) = s` for all :math:`s \in s`), we can compute the
parity of the size of :math:`S` by counting the number of elements fixed
by :math:`f`. In other words, we can pair up elements in a set that
cancel each other out.

Definitions
-----------

Let’s collect some terminology we will use:

-  The **binary representation** of a nonnegative integer :math:`x` is
   the unique set of powers of :math:`2` that sum to :math:`x`.

-  If :math:`a` and :math:`b` are integers, we say :math:`a` is a
   **submask** of :math:`b` if the powers of :math:`2` in the binary
   representation of :math:`a` are also in the binary representation of
   :math:`b`.

Overview
--------

Our high-level plan will be as follows. Since any element in a good
array will be a submask of :math:`y`, the total score will also be a
submask of :math:`y`. Therefore let’s compute the total answer by
counting the total contribution of each power of :math:`2` in the binary
representation of :math:`y`. If :math:`2^i` appears an odd number of
times among all elements of all good arrays, then we add :math:`2^i` to
the answer; otherwise, we add :math:`0`.

So, for each power of :math:`2`, we want to count the parity of the
number of times it appears among all good arrays. We will need some way
of representing the conditions that the sum of a good array is
:math:`x`, and that the bitwise or of a good array is :math:`y`.
However, it turns out that this bitwise or condition is a bit unwieldy,
and it is easier to work with the relaxed constraint that the bitwise or
is simply a submask of :math:`y`. We can recover the original constraint
by using the inclusion-exclusion principle and considering all submasks
of :math:`y`.

This sounds good so far, but we still haven’t dealt with the meat of the
problem–counting the number of arrays whose sum is :math:`x` with some
particular constraints. Moreover, by using inclusion-exclusion and
considering each power of :math:`2` independently, we have forced
ourselves to iterate over :math:`O(y \log y)` (bit, mask) pairs, so
ideally, we would be able to compute this number in constant time or at
least :math:`O(\log y)`. Since we are only concerned with the *parity*
of the number of arrays, it turns out we can compute this in
:math:`O(1)` with the help of some number theory (`Lucas’
Theorem <https://en.wikipedia.org/wiki/Lucas%27s_theorem>`__) and some
clever pairing-up arguments.

Details
=======

Matrix Fun
----------

We assume :math:`n` is odd. Let :math:`B = \begin{bmatrix}
  b_1 & b_2 & \dots & b_k
\end{bmatrix}` be the powers of :math:`2` in the binary representation
of :math:`y`. For instance, if :math:`y = 13`, then
:math:`B = \begin{bmatrix}
  2^0 & 2^1 & 2^3
\end{bmatrix}`. If :math:`A` is a good array, since
:math:`a_1 | a_2 | \dots | a_n = y`, :math:`a_i` is a submask of
:math:`y`. We can imagine “redistributing” the bits in :math:`A` to
produce a new good array. More precisely, given a good array :math:`A`,
let :math:`c_i` be the number of elements that have :math:`b_i` in their
binary representation. Since :math:`a_1 | a_2 | \dots | a_n = y`,
:math:`c_i \geq 1`, and since there are :math:`n` elements in an array,
:math:`c_i \leq n`. Let
:math:`C = \begin{bmatrix} c_1 & c_2 & \dots & c_k \end{bmatrix}^\top`.
Since :math:`a_1 + a_2 + \dots + a_n = x`, we have
:math:`BC = c_1 b_1 + c_2 b_2 + \dots + c_k b_k = x`, and there are

.. math:: F(C) = {n \choose c_1} {n \choose c_2} \dots {n \choose c_k}

ways to redistribute bits to obtain new good arrays with the same
:math:`C` vector. Each good array corresponds to some :math:`C`, and we
can compute the total score by computing the scores of each of the
:math:`F(C)` good arrays corresponding to :math:`C`. If :math:`F(C)` is
even, then since each :math:`b_i` appears an even number of times, the
score of all :math:`F(C)` arrays is :math:`0`. If :math:`F(C)` is odd,
the score of all :math:`F(C)` arrays is the xor of all :math:`b_i`,
where :math:`c_i` is odd.

By `Lucas’ Theorem <https://en.wikipedia.org/wiki/Lucas%27s_theorem>`__,
:math:`{n \choose c_i}` is odd if and only if :math:`c_i` is a submask
of :math:`n`. In order for :math:`F(C)` to be odd, all
:math:`{n \choose c_i}` must be odd, so :math:`c_i` is a submask of
:math:`n` for all :math:`i`. Therefore, let’s rewrite our equation
:math:`BC = x` into a form where we are only considering solutions where
:math:`c_i` is a submask of :math:`n`. Let :math:`D = \begin{bmatrix}
  d_1 & d_2 & \dots & d_l
\end{bmatrix}^\top` be the powers of :math:`2` in the binary
representation of :math:`n` (since :math:`n` is odd, let’s assume
:math:`d_1 = 1` for notational convenience). Then since :math:`c_i` is a
submask of :math:`n`, we can represent :math:`c_i` with the row vector
:math:`E_i = \begin{bmatrix}
  e_{i, 1} & e_{i, 2} & \dots & e_{i, l}
\end{bmatrix}`, where :math:`e_{i, j} \in \{0, 1\}` and
:math:`c_i = E_i D`. Let :math:`E` be the matrix of all :math:`E_i`, so

.. math::

   E = \begin{bmatrix}
     e_{1, 1} & e_{1, 2} & \dots & e_{1, l} \\
     e_{2, 1} & e_{2, 2} & \dots & e_{2, l} \\
       \vdots & \vdots   & \ddots & \vdots \\
     e_{k, 1} & e_{k, 2} & \dots & e_{k, l} \\
     \end{bmatrix}
     \text{ and } C = ED.

Then

.. math::

   x = BC = BED =
     \begin{bmatrix}
       b_1 & b_2 \dots & b_k
     \end{bmatrix}
     \begin{bmatrix}
     e_{1, 1} & e_{1, 2} & \dots & e_{1, l} \\
     e_{2, 1} & e_{2, 2} & \dots & e_{2, l} \\
       \vdots & \vdots   & \ddots & \vdots \\
     e_{k, 1} & e_{k, 2} & \dots & e_{k, l} \\
     \end{bmatrix}
     \begin{bmatrix}
       d_1 \\ d_2 \\ \vdots \\ d_l
     \end{bmatrix}.

Each possible binary matrix :math:`E` corresponds to a choice of
:math:`C` where each :math:`c_i` is a submask of :math:`n`. Let’s call
matrix :math:`E` **valid** if :math:`BED = x`. For each valid matrix
where each row in :math:`E` has a nonzero entry (i.e.,
:math:`c_i \geq 1`), we add :math:`b_i` to the xor-sum for each
:math:`i` such that :math:`e_{i, 1} = 1` (i.e., :math:`c_i` is odd).

Inclusion-Exclusion
-------------------

Let’s compute the total score by computing the contribution of each
:math:`b_i`. We will add :math:`b_i` to our total score exactly when
there is an odd number of valid matrices :math:`E` with
:math:`e_{i, 1} = 1`. However, recall that :math:`E` needs to satisfy
the bitwise or condition as well: for each :math:`c_i`, we must have
:math:`1 \leq c_i`, which means that for each :math:`i`, at least one
:math:`e_{i, j}` in the :math:`i`\ ’th row must be :math:`1`. The
problem is that this is a difficult constraint to work with; we’ve
already used this binary matrix representation to encode the constraint
that each :math:`c_i` must be a submask of :math:`n`, but it’s harder to
force each row to have a nonzero element.

Let’s work around this problem by relaxing this constraint, and then
recovering the original answer using the inclusion-exclusion principle
over all submasks of :math:`y`. More precisely, suppose :math:`y'` is a
submask of :math:`y`. Let :math:`g(i, y')` be the parity of the number
of matrices :math:`E` where :math:`e_{i, 1} = 1` and the :math:`k`\ ’th
row in :math:`E` is allowed to have nonzero entries only when
:math:`d_k` is in the binary representation of :math:`y'`. Importantly,
we don’t require here that :math:`c_i \geq 1`. Then
:math:`g(i, y') = \bigoplus_{y' \subseteq y} g(i, y')`. This is the same
idea as regular inclusion-exclusion, except we don’t have to worry about
signs since we only care about parity.

So now all we have to do is solve this relaxed problem for each
:math:`i` and each submask :math:`y'`. The issue is that there are
:math:`O(y)` submasks and :math:`O(\log y)` powers of :math:`2` to
handle, so we’re already up to :math:`O(y \log y)` complexity, and we
still haven’t dealt with how to count the number of solutions to this
very large subset sum problem. However, keep in mind that we are only
interested in the parity of the number of solutions, and this is again
where symmetry comes into play. Consider some valid matrix :math:`E`.
For each nonzero entry :math:`e_{i, j}`, we can think of
:math:`e_{i, j}` as “selecting” a pair of terms :math:`b_i d_j` to sum
to :math:`x`. Instead of thinking of our solution space as all possible
binary matrices :math:`E`, let’s think of it as multisets of terms of
the form :math:`b_i d_j`, where we select some subset to sum to
:math:`x`. Then it turns out we have a simple condition to determine the
parity of the number of ways to sum to :math:`x`:

[lemma:2] Let :math:`T` be a multiset of powers of :math:`2` whose sum
is :math:`S`. The number of ways to select a subset of :math:`T` to sum
to :math:`x` is odd if and only if :math:`x` is a submask of :math:`S`.

Suppose we have two equal numbers in our multiset; let’s call them
:math:`a` and :math:`b`. If we have a subset that includes :math:`a` but
not :math:`b`, we can pair it up with a nearly identical subset that
includes :math:`b` but not :math:`a`, and these two subsets have the
same sum. Thus if we have two equal numbers in our multiset, we only
have to count the number of solutions where we either include both of
them or ignore both of them, since by this pairing argument, the number
of solutions where we include just one of them is even. However, if we
are always either including or ignoring two terms equal to some power
:math:`2^k`, we might as well replace them with the single term
:math:`2^{k+1}`. More precisely, if our multiset is :math:`T`, there is
a bijection between

.. math::

   \begin{aligned}
   \\
       \leftrightarrow [\text{subsets of $T \setminus \{2^k, 2^k\} \cup \{2^{k+1}\}$}].
     \end{aligned}

Note that these two multisets maintain the same sum.

Moreover, we can iteratively repeat this process until we have no more
duplicate numbers in our multiset. At the end of this process, we have
some set :math:`T'` of unique powers of :math:`2` whose sum is still
:math:`S`, and we can form a sum of :math:`x` exactly when :math:`x` is
a submask of the :math:`S`.

Let’s apply this observation to solve our subproblem. Given :math:`i`
and a submask :math:`y'`, our multiset :math:`T` is the set of terms
:math:`\{ b_i d_j, 1 \leq i \leq k, 1 \leq j \leq l, b_i \in y' \}`
(which are all powers of :math:`2` since :math:`b_i` and :math:`d_j` are
powers of :math:`2`), where :math:`b_i` is in the binary representation
of :math:`y'`. Since :math:`\sum d_j = n`, :math:`T` has sum
:math:`ny'`. We can assume that :math:`e_{i, 1} = 1`, so let’s take this
out of our multiset, so now our multiset is
:math:`T' = T \setminus \{b_i\}` with sum :math:`ny' - b_i`. By our
Lemma `[lemma:2] <#lemma:2>`__, we have an odd number of solutions if
and only if :math:`x - b_i` is a submask of :math:`ny' - b_i`.

Putting it all together
-----------------------

To summarize:

-  Count the contribution of each bit independently.

-  Use inclusion-exclusion to sum over all submasks of :math:`y`.

-  We can solve this relaxed subproblem by checking if :math:`x - b_i`
   is a submask of :math:`ny' - b_i`.

Despite some of the elaborate reasoning required, the resulting
implementation is remarkably simple. I’ll leave my
`submission <https://codeforces.com/contest/1770/submission/188138802>`__
here for reference.

Vandermonde Solution
====================

The editorial provides a shorter method of arriving at the same
implementation of the solution described above using Lucas’ theorem and
`Vandermonde’s
identity <https://en.wikipedia.org/wiki/Vandermonde's_identity>`__.
Again, we’ll count the contribution of each power of :math:`2` in the
binary representation of :math:`y` and use inclusion-exclusion to
xor-sum over all submasks of :math:`y`. We wish to count the parity of
the number of solutions to

.. math:: a_1 + a_2 + \dots + a_n = x,

where each :math:`a_i` is a submask of :math:`y'`, and :math:`b_i` is in
the binary representation of :math:`a_1`. (Since each :math:`a_j`
provides the same contribution to the total score and :math:`n` is odd,
the total score is equal to the contribution of a single :math:`a_j`.)
We can assume we have already added :math:`b_i` to the sum, so then
:math:`a_i` must be a submask of :math:`y' - b_i`. Using Lucas’ theorem,
we can encode these submask constraints as the parity of

.. math:: {y' - b_i \choose a_1} {y' \choose a_2} \dots {y' \choose a_n},

since this product will be odd if and only if each binomial coefficient
is odd, which requires that :math:`a_j` is a submask of :math:`y'` (or
:math:`y' - b_i` in the case of :math:`a_1`). Thus, we can count the
parity of the number of solutions as

.. math::

   \sum_{a_1 + a_2 + \dots + a_n = x - b_i} 
     {y' - b_i \choose a_1} {y' \choose a_2} \dots {y' \choose a_n}
     \pmod{2}.

By Vandermonde’s identity, this is equal to

.. math:: {ny' - b_i \choose x - b_i} \pmod{2}.

Again by Lucas’ theorem, we just need to check if :math:`x - b_i` is a
submask of :math:`ny' - b_i`. I find this solution particularly
remarkable, since binomial coefficients do not appear in either the
problem statement or the final implementation; they are only used an
intermediate step.
