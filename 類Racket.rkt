#lang racket
#|
    Copyright (C) 2018  Zaoqi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
|#
(provide 譯 讀)
(define ++ string-append)
(define (譯 x)
  (match x
    [(cons #%brackets (? list? xs)) (apply 列 (建名 "！" "式") (map 譯 xs))]
    [(? list? xs) (apply 列 (map 譯 xs))]
    [(? char? c) (字 c)]
    [(? hash? h) (映 (hash->list h))]
    ['() 空]
    [#f 陰]
    [#t 陽]
    [(? symbol? s) (符 s)]
    ))
(define 空 "空")
(define 陰 "陰")
(define 陽 "陽")
(define (名 . xs)
  (++ "名"(apply 列 xs)))
(define (列 . xs)
  (++ "("(apply ++ (add-between xs " "))")"))
(define (简名 s)
  (简名-字列 (string->list s)))
(define (简名-字列 cs)
  (apply 名 (map 字 cs)))
(define (建名 . xs)
  (apply 名 (map 简名 xs)))
(define (符 s) (apply 名 (%符 (string->list (symbol->string s)))))
(define (%符 s)
  (match s
    [(list c ... (or #\？ #\?)) (append (%符 c) (list (简名 "？")))]
    [(list (and a (not #\-)) ... #\- d ...) (cons (简名-字列 a) (%符 d))]
    [(list (and a (not #\→)) ... #\→ (and d (not #\→)) ...) (append (%符 a) (list (简名-字列 "→")) (%符 d))]
    [_ (list (简名-字列 s))]
    ))
(define (字 c)
  (++ "字"(string c)))
(define (映 ps)
  (++ "映"(apply 列 (map (λ (p) (列 (car p) (cdr p))) ps))))
(define (讀 . 參)
  (parameterize ([read-square-bracket-with-tag #t])
    (譯 (apply read 參))))
