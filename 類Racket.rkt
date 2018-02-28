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
    [(? symbol? s) (符 (symbol->string s))]
    ))
(define 空 "空")
(define 陰 "陰")
(define 陽 "陽")
(define (字 c)
  (++ "字"(string c)))
(define (映 ps)
  (++ "映"(apply 列 (map (λ (p) (列 (car p) (cdr p))) ps))))
(define (讀 . 參)
  (parameterize ([read-square-bracket-with-tag #t])
    (譯 (apply read 參))))
