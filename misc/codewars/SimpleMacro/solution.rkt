#lang racket
(provide last-symbol)

(define-syntax-rule (last-symbol ... last)
  'last)