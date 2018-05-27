#lang racket
{provide
 等？
 <陰，陽>.？ <陰，陽>.陰.？ <陰，陽>.陰.其 <陰，陽>.陽.？ <陰，陽>.陽.其 <陰，陽>.若+
 列.？ 列.連.？ 列.連.建+ 列.連.首+ 列.連.尾+ 列.空.？ 列.空.其
 名.？ 名.文.？ 名.構.？ 名.構.建+ 名.構.:名+ 名.構.:列+
 表.？ 表.空 表.增+ 表.改+ 表.取+ 表.含？ 表.删+ 表.→列
 }
{module rec racket
  {provide define-rec}
  {define-syntax-rule {define-rec is? (f p ...)}
    {begin
      {define s (string->symbol (string-append "rec:" (symbol->string 'f)))}
      {define (f p ...) `#(,s ,p ...)}
      {define (is? x) (and (vector? x) (< 0 (vector-length x)) (eq? (vector-ref x 0) s))}
      {hel is? 1 (p ...)}}}
  {define-syntax hel
    {syntax-rules ()
      [(_ is? n (p)) {define (p x) (if (is? x) (vector-ref x n) (error))}]
      [(_ is? n (p . ps))
       {begin
         {define (p x) (if (is? x) (vector-ref x n) (error))}
         {define n2 (+ n 1)}
         {hel is? n2 ps}}]}}
  }{require 'rec}
{require (only-in lazy [if lazy-if] equal?)}

{define 等？ equal?}

{define <陰，陽>.？ boolean?}
{define (<陰，陽>.陰.？ x) (eq? x #f)}
{define <陰，陽>.陰.其 #f}
{define (<陰，陽>.陽.？ x) (eq? x #t)}
{define <陰，陽>.陽.其 #t}
{define <陰，陽>.若+ lazy-if}

{define (列.？ x) (or (列.連.？ x) (列.空.？ x))}
{define 列.連.？ pair?}
{define 列.連.建+ cons}
{define 列.連.首+ car}
{define 列.連.尾+ cdr}
{define 列.空.？ null?}
{define 列.空.其 '()}

{define (名.？ x) (or (名.文.？ x) (名.構.？ x))}
{define 名.文.？ symbol?}
{define-rec 名.構.？ (名.構.建+ 名.構.:名+ 名.構.:列+)}

{define-rec 表.？ (#%表 #%un表)}
;{define 表.空 (#%表 (make-immutable-hash-lazy))}
{define 表.空 (#%表 '())}
{define (表.增+ :表 名 :物) (#%表 (dict-set (#%un表 :表) 名 :物))}
{define (表.改+ :表 名 :化) (#%表 (dict-update (#%un表 :表) 名 :化))}
{define (表.取+ :表 名) (dict-ref (#%un表 :表) 名)}
{define (表.含？ :表 名) (dict-has-key? (#%un表 :表) 名)}
{define (表.删+ :表 名) (dict-remove (#%un表 :表) 名)}
{define (表.→列 :表) (map (λ (p) (list (car p) (cdr p))) (dict->list (#%un表 :表)))}
