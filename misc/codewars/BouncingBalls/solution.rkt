#lang racket
(provide bouncing-balls)

(define (bouncing-balls h bounce window)
  (define (go h bounce window)
    (if (<= (* bounce h) window)
        1
        (+ 2 (go (* h bounce) bounce window))))
  (if (and (> h 0) (> bounce 0) (< bounce 1) (< window h))
      (go h bounce window)
      -1)
)