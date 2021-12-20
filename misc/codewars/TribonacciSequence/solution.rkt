#lang racket

(provide tribonacci)



(define (tribonacci sign n)
  (define (trib seq n)
    (match seq
      [(cons x (cons y (cons z zz)))
       (if (= n 0)
        seq
        (trib (cons (+ x y z) seq) (sub1 n)))]))
  (match sign
    [(list x y z)
     (case n
       ((0) '())
       ((1) (list x))
       ((2) (list x y))
       (else (reverse (trib (reverse sign) (- n 3))))
      )
     ]))