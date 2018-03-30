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
{require srfi/9}
{provide
 名/文？ 名/文 名/文-1 名/構？ 名/構 名/構.名 名/構.列 名？
 等？
 首-尾 首-尾？ 首-尾.首 首-尾.尾 空 空？
 文？
 映？ 映/空 映.增-改 映.取 映.含？ 映.删 映→列
 #%機 機 機？ #%機.境 機.形 #%機.物
 #%機-內 #%機-內.p #%機-內.形 #%機-內.物
 陰 楊 #%若
 引-機 引-機？ 引-機-1
 誤 誤？ 誤-1
 構 構？ 構.名 構.列
 }

{define (等？ 甲 乙) (#%EQ? (make-hasheq) 甲 乙)}
{define #%_ (set)}
{define (#%EQ? h 甲 乙)
  (or
   (eq? 甲 乙)
   (set-member? (hash-ref h 甲 #%_) 乙)
   (set-member? (hash-ref h 乙 #%_) 甲)
   {begin
     (hash-update! h 甲 {λ (v) (set-add! v 乙)} mutable-seteq)
     {cond
       [(promise? 甲) (#%EQ? h (force 甲) 乙)]
       [(promise? 乙) (#%EQ? h 甲 (force 乙))]
       [else
        {match 甲
          [(cons a1 d1) {match 乙 [(cons a2 d2) (and (#%EQ? h a1 a2) (#%EQ? h d1 d2))] [_ #f]}]
          [(? 映？) (and (映？ 乙) (#%EQ? h (映→列 甲) (映→列 乙)))]
          [(? 名/文？) (and (名/文？ 乙) (#%EQ? h (名/文-1 甲) (名/文-1 乙)))]
          [(? 名/構？)
           (and (名/構？ 乙)
                (#%EQ? h (名/構.名 甲) (名/構.名 乙))
                (#%EQ? h (名/構.列 甲) (名/構.列 乙)))]
          [(#%機 境1 形1 物1)
           {match 乙
             [(#%機 境2 形2 物2)
              (and (#%EQ? h 境1 境2)
                   (#%EQ? h 形1 形2)
                   (#%EQ? h 物1 物2))]
             [_ #f]}]
          [(引-機 x) (match 乙 [(引-機 y) (#%EQ? h x y)] [_ #f])]
          [(誤 x) (match 乙 [(誤 y) (#%EQ? h x y)] [_ #f])]
          [(構 名1 列1)
           {match 乙
             [(構 名2 列2)
              (and (#%EQ? h 名1 名2)
                   (#%EQ? h 列1 列2))]
             [_ #f]}]
          [_ (equal? 甲 乙)]}]}})}

{define 首-尾 cons}
{define 首-尾？ pair?}
{define 首-尾.首 car}
{define 首-尾.尾 cdr}
{define 空？ null?}
{define 空 '()}

{define 文？ char?}

{define-custom-hash-types 映 等？}
{define 映？ immutable-映?}
{define 映/空 (make-immutable-映)}
{define 映.增-改 dict-set}
{define 映.取 dict-ref}
{define 映.删 dict-remove}
{define 映.含？ dict-has-key?}
{define 映→列 dict->list}

{define-custom-hash-types mh 等？}
{define gen/c
  {let ([c 0])
    {λ ()
      {let ([v (+ 1 c)])
        (set! c v)
        v}}}}
{define (gen/s) (string->symbol (number->string (gen/c)))}
{define h-名/文:sym->_ (make-hasheq)}
{define h-名/文:_->sym (make-mutable-映)}
{define (名/文 列)
  (dict-ref
   h-名/文:_->sym 列
   {λ ()
     {let ([s (gen/s)])
       (dict-set! h-名/文:sym->_ s 列) ; 可能bug： 多處理器時
       (dict-set! h-名/文:_->sym 列 s)
       s}})}
{define (名/文？ 甲) (dict-has-key? h-名/文:sym->_ 甲)}
(define (名/文-1 名/文) (dict-ref h-名/文:sym->_ 名/文))
(define h-名/構:sym->pair (make-hasheq))
(define h-名/構:pair->sym (make-mutable-映))
(define (名/構 名 列)
  (let ([p (cons 名 列)])
    (dict-ref
     h-名/構:pair->sym p
     (λ ()
       (let ([s (gen/s)])
         (dict-set! h-名/構:sym->pair s p)
         (dict-set! h-名/構:pair->sym p s))))))
(define (名/構？ 甲) (dict-has-key? h-名/構:sym->pair 甲))
(define (名/構.名 名/構) (car (dict-ref h-名/構:sym->pair 名/構)))
(define (名/構.列 名/構) (cdr (dict-ref h-名/構:sym->pair 名/構)))
(define (名？ 甲) (or (名/文？ 甲) (名/構？ 甲)))

(struct #%機 (境 形 物))
(struct #%機-內 (p 形 物))
(define (機 形 物) (#%機 映/空 形 物))
(define (機？ 甲) (or (#%機? 甲) (#%機-內? 甲)))
(define #%機？ #%機?)
(define #%機-內？ #%機-內?)
(define #%機-內.形 #%機-內-形)
(define #%機-內.物 #%機-內-物)
(define #%機-內.p #%機-內-p)
(define #%機.境 #%機-境)
(define (機.形 甲) (if (#%機? 甲) (#%機-形 甲) (#%機-內-形 甲)))
(define #%機.物 #%機-物)

(define 陰 #f)
(define 楊 #t)
(define-syntax-rule (#%若 b x y) (if b x y))

(struct 引-機 (機))
(define 引-機？ 引-機?)
(define 引-機-1 引-機-機)

(struct 誤 (物))
(define 誤？ 誤?)
(define 誤-1 誤-物)

(struct 構 (名 列))
(define 構？ 構?)
(define 構.名 構-名)
(define 構.列 構-列)
