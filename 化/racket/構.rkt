#lang racket
{require (only-in lazy [if lazy-if] equal?)}
{define-custom-hash-types hash-lazy equal?}
;{define (memroize1/forever f)
;  {let ([h (make-mutable-hash-lazy)])
;    {λ (x)
;      (dict-ref! h x {λ () (f x)})}}}
;{define (memroize*/forever f)
;  {let ([h (make-mutable-hash-lazy)])
;    {λ xs
;      (dict-ref! h xs {λ () (apply f xs)})}}}
;{define-syntax-rule {define/memroize1/forever (f x) v} {define f (memroize1/forever {λ (x) v})}}
{define-syntax-rule {define/memroize*/forever (f x ...) v}
  {define f
    {let ([h (make-mutable-hash-lazy)])
      {λ (x ...)
        (dict-ref! h `(,x ...) {λ () v})}}}}
{provide
 等？
 陰 陽 陰-陽.若
 :列/連？ →列/連 列/連.首 列/連.尾 其:列/空
 :名/文？ →名/構 :名/構？ 名/構.:名 名/構.:列
 :表？ 空:表 表.增 表.改 表.取 表.含？ 表.删 表→列
 :集？ 空:集 集.增 集.含？ 集.删 集→列
 :化？ →化 #%化.內 #%→化/內 化.形 化.:物
 →式 :式？ →式-1
 →構 →構？ 構.:名 構.:列
 →誤 :誤？ →誤-1

 :名？
 }
{define 等？ equal?}

{define 陰 #f}
{define 陽 #t}
{define 陰-陽.若 lazy-if}

{define :列/連？ pair?}
{define →列/連 cons}
{define 列/連.首 car}
{define 列/連.尾 cdr}
{define 其:列/空 '()}

{define :名/文？ symbol?}
{struct 名/構 (:名 :列) #:transparent}
{define/memroize*/forever (→名/構 :名 :列) (名/構 :名 :列)}
{define :名/構？ 名/構?}
{define 名/構.:名 名/構-:名}
{define 名/構.:列 名/構-:列}

{define :表？ immutable-hash-lazy?}
{define 空:表 (make-immutable-hash-lazy)}
{define 表.增 dict-set}
{define 表.改 dict-update}
{define 表.取 dict-ref}
{define 表.含？ dict-has-key?}
{define 表.删 dict-remove}
{define (表→列 :表) (map (λ (p) (list (car p) (cdr p))) (dict->list :表))}

{struct 集 (:表) #:transparent}
{define :集？ 集?}
{define 空:集 (集 空:表)}
{define (集.增 :集 :物) (集 (表.增 (集-:表 :集) :物 #t))}
{define (集.含？ :集 :物) (表.含？ (集-:表 :集) :物)}
{define (集.删 :集 :物) (集 (表.删 (集-:表 :集) :物))}
{define (集→列 :集) (map 列/連.首 (表→列 (集-:表 :集)))}

{struct 化 (內 形 :物) #:transparent}
{define :化？ 化?}
{define (→化 形 :物) (化 #f 形 :物)}
{define #%化.內 化-內}
{define #%→化/內 化}
{define 化.形 化-形}
{define 化.:物 化-:物}

{struct →式 (:物) #:transparent}
{define :式？ →式?}
{define →式-1 →式-:物}

{struct →構 (:名 :列) #:transparent}
{define →構？ →構?}
{define 構.:名 →構-:名}
{define 構.:列 →構-:列}

{struct →誤 (:物) #:transparent}
{define :誤？ →誤?}
{define →誤-1 →誤-:物}

{define (:名？ :物) (or (:名/文？ :物) (:名/構？ :物))}
