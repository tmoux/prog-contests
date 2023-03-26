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
      (testcases 1
                 (getparams (N K)
                            (displayln N K)
                            (displayln (genarray N (lambda (x) (randrange 1 K))))
                            (displayln (genarray N (lambda (x) (randrange 1 2))))
                            )))
