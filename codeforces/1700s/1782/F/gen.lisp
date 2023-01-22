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
      (dln (randrange 1 10) (randrange 0 10000))
      )
