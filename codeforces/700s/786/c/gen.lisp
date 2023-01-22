(load "~/.quicklisp/setup.lisp")
(ql:quickload "quickgen")
(in-package :quickgen)

;; (exec "gen"
;;       (getparams (c N M)
;;                  (testcases c
;;                  (displayln N M)
;;                  (displayln (genarray M (lambda (x) (randrange 0 x))))
;;                  (displayln (genperm M :idx 1))
;;                  )))

(exec "gen"
      (getparams (N)
                 (dln N)
                 (dln (genarray N (lambda (x) (randrange 1 N))))))
