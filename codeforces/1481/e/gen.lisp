(load "~/.quicklisp/setup.lisp")
(ql:quickload "quickgen")
(in-package :quickgen)

(exec "gen"
      (getparams (N)
                 (dln N)
                 (dln (genarray N (lambda (x) (randrange 1 N))))))
