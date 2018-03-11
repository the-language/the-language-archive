;;    語
;;    Copyright (C) 2017-2018  Zaoqi

;;    This program is free software: you can redistribute it and/or modify
;;    it under the terms of the GNU Affero General Public License as published
;;    by the Free Software Foundation, either version 3 of the License, or
;;    (at your option) any later version.

;;    This program is distributed in the hope that it will be useful,
;;    but WITHOUT ANY WARRANTY; without even the implied warranty of
;;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;    GNU Affero General Public License for more details.

;;    You should have received a copy of the GNU Affero General Public License
;;    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

(define-values (名？ 列→名 名→列)
  ((λ ()
     (define h-un (make-hash))
     (define h (make-hash))
     (define c 0)
     (define (名？ 甲) (hash-has-key? h 甲))
     (define (列→名 列)
       (hash-ref
        h 列
        (λ ()
          (let ([s (string->symbol (number->string c))])
            (set! c (+ c 1))
            (hash-set! h-un s 列)
            (hash-set! h 列 s)
            s))))
     (define (名→列 名) (hash-ref h-un 名))
     (values 名？ 列→名 名→列))))

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

(define-record-type 機-引
  (機-引 機)
  機-引？
  (機 機-引/反))
(define-record-type 機-譯
  (機-譯 機)
  機-譯？
  (機 機-譯/反))

(define-record-type 誤
  (誤 甲)
  誤？
  (甲 誤/反))

(define-record-type 構
  (構 名 列)
  構？
  (名 構/名)
  (列 構/列))
