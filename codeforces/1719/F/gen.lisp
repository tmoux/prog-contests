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
      (getparams (n)
                 (testcases 1
                            (let ((q 200000) (b 1000000000))
                              (dln n q)
                              (dln (genarray n (lambda (x) (randrange 1 b))))
                              (dotimes (i q)
                                (dln (randrange 1 n) (randrange 1 b)))))))
