#lang typed/racket

(define-type SnailNum
  (U Number (Pair SnailNum SnailNum)))

(: ex SnailNum)
(define ex (cons 3 5))
