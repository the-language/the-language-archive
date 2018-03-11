#lang racket
(require srfi/9)
(define (id x) x)

(define 等？ equal?) ; BUG

(define 首-尾 cons)
(define 首-尾？ pair?)
(define 首-尾.首 car)
(define 首-尾.尾 cdr)
(define 空？ null?)
(define 空 '())
(define 字？ char?)
(define-record-type 名
  (列→名 列)
  名？
  (列 名→列))

(define-custom-hash-types 映 等？)
(define 映？ immutable-映?)
(define 映/空 (make-immutable-映))
(define 映/改 dict-set)
(define 映/取 dict-ref)
(define 映/删 dict-remove)
(define 映/含？ dict-has-key?)

(define-record-type 機
  (機+境 境 形 物)
  機？
  (形 機/形)
  (物 機/物-無-境))

(define 陰 #f)
(define 楊 #t)
