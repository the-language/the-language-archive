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
{provide
 名/文？ 名/文 名/文-1 名/構？ 名/構 名/構.名 名/構.列 名？ symbol→名 引
 等？
 首-尾 首-尾？ 首-尾.首 首-尾.尾 空 空？
 文？
 集/定？ 集/定/空 集/定.增 集/定.改 集/定.增-改 集/定.取 集/定.含？ 集/定.删 集/定→列
 #%機 #%機？ #%機.形 #%機.物
 #%機-內 #%機-內？ #%機-內.p #%機-內.形 #%機-內.物
 機 機？ 機.形 機.物
 列
 陰 陽 陰-陽？
 式 式？ 式-1
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
          [(? 集/定？) (and (集/定？ 乙) (#%EQ? h (集/定→列 甲) (集/定→列 乙)))]
          [(? 名/文？) (and (名/文？ 乙) (#%EQ? h (名/文-1 甲) (名/文-1 乙)))]
          [(? 名/構？)
           (and (名/構？ 乙)
                (#%EQ? h (名/構.名 甲) (名/構.名 乙))
                (#%EQ? h (名/構.列 甲) (名/構.列 乙)))]
          [(#%機 形1 物1)
           {match 乙
             [(#%機 形2 物2)
              (and (#%EQ? h 形1 形2)
                   (#%EQ? h 物1 物2))]
             [_ #f]}]
          [(#%機-內 _ 形1 物1)
           {match 乙
             [(#%機-內 _ 形2 物2)
              (and (#%EQ? h 形1 形2)
                   (#%EQ? h 物1 物2))]
             [_ #f]}]
          [(式 x) (match 乙 [(式 y) (#%EQ? h x y)] [_ #f])]
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

{define-custom-hash-types 集/定 等？}
{define 集/定？ immutable-集/定?}
{define 集/定/空 (make-immutable-集/定)}
{define 集/定.增 dict-set}
{define 集/定.增-改 dict-set}
{define 集/定.改 dict-update}
{define 集/定.取 dict-ref}
{define 集/定.删 dict-remove}
{define 集/定.含？ dict-has-key?}
{define 集/定→列 dict->list}

{define-custom-hash-types mh 等？}
{define gen/c
  {let ([c 0])
    {λ ()
      {let ([v (+ 1 c)])
        {set! c v}
        v}}}}
{define (gen/s) (string->symbol (number->string (gen/c)))}
{define h-名/文:sym->_ (make-hasheq)}
{define h-名/文:_->sym (make-mutable-集/定)}
{define (名/文 列)
  (dict-ref
   h-名/文:_->sym 列
   {λ ()
     {let ([s (gen/s)])
       (dict-set! h-名/文:sym->_ s 列) ; 可能bug： 多處理器時
       (dict-set! h-名/文:_->sym 列 s)
       s}})}
{define (名/文？ 甲) (dict-has-key? h-名/文:sym->_ 甲)}
{define (名/文-1 名/文) (dict-ref h-名/文:sym->_ 名/文)}
{define h-名/構:sym->pair (make-hasheq)}
{define h-名/構:pair->sym (make-mutable-集/定)}
{define (名/構 名 列)
  {let ([p (cons 名 列)])
    (dict-ref
     h-名/構:pair->sym p
     {λ ()
       {let ([s (gen/s)])
         (dict-set! h-名/構:sym->pair s p)
         (dict-set! h-名/構:pair->sym p s)}})}}
{define (名/構？ 甲) (dict-has-key? h-名/構:sym->pair 甲)}
{define (名/構.名 名/構) (car (dict-ref h-名/構:sym->pair 名/構))}
{define (名/構.列 名/構) (cdr (dict-ref h-名/構:sym->pair 名/構))}
{define (名？ 甲) (or (名/文？ 甲) (名/構？ 甲))}

{struct #%機 (形 物)}
{define #%機？ #%機?}
{define #%機.形 #%機-形}
{define #%機.物 #%機-物}
{struct #%機-內 (p 形 物)}
{define #%機-內？ #%機-內?}
{define #%機-內.p #%機-內-p}
{define #%機-內.形 #%機-內-形}
{define #%機-內.物 #%機-內-物}
{define 機 #%機}
{define (機？ 甲) (or (#%機？ 甲) (#%機-內？ 甲))}
{define (機.形 甲) (if (#%機? 甲) (#%機.形 甲) (#%機-內.形 甲))}
{define (機.物 甲) (if (#%機? 甲) (#%機-物 甲) (#%機-內.物 甲))}

{define 列 list}

{define 陰 #f}
{define 陽 #t}
{define 陰-陽？ boolean?}

{struct 式 (機)}
{define 式？ 式?}
{define 式-1 式-機}

{struct 誤 (物)}
{define 誤？ 誤?}
{define 誤-1 誤-物}

{struct 構 (名 列)}
{define 構？ 構?}
{define 構.名 構-名}
{define 構.列 構-列}

{define memorize1
  {let ([h (make-hasheq)])
    {λ (f)
      {λ (x)
        (hash-ref! h x {λ () (f x)})}}}}

{define-values (symbol→名)
  ({λ ()
     {define (symbol→名 s) (mkn (string->list (symbol->string s)))}
     {define-syntax-rule {定-名/文 s}
       {define s (名/文 (string->list (symbol->string {quote s})))}}
     {define-syntax-rule {定-名/文* x ...}
       {begin {定-名/文 x} ...}}
     {定-名/文* 乎 反 式 以 子 列 化}
     {define mkn
       {match-lambda
         [(list cs ... #\？) (名/構 乎 (list (mkn cs)))]
         [(list cs ... #\- #\1) (名/構 反 (list (mkn cs)))]
         [(list #\！ cs ...) (名/構 式 (list (mkn cs)))]
         [(list (and (not #\.) cs0) ... #\. (and (not #\.) cs1) ...) (名/構 以 (list (mkn cs0) (mkn cs1)))]
         [(list (and (not #\→) cs0) ... #\→ (and (not #\→) cs1) ...) (名/構 化 (list (mkn cs0) (mkn cs1)))]
         [(list 甲-集 ... #\/ (and (not #\/) 乙-集) ...) (名/構 子 (list (mkn 甲-集) (mkn 乙-集)))]
         [(list (and (not #\-) 甲-集) ... #\- 乙-集 ...) (mk列 (list (mkn 甲-集)) 乙-集)]
         [xs (名/文 xs)]}}
     {define (mk列 xs cs)
       {match cs
         [(list (and (not #\-) 甲-集) ... #\- 乙-集 ...) (mk列 (append xs (list (mkn 甲-集))) 乙-集)]
         [甲-集 (名/構 列 (append xs (list (mkn 甲-集))))]}}
     (values (memorize1 symbol→名))})}

{define-syntax-rule {引 名} (symbol→名 {quote 名})}
