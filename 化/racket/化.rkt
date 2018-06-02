#lang lazy
; WIP
{require racket/dict}
{define-custom-hash-types hash-lazy equal?}

{define-syntax-rule {入 . xs} {λ . xs}}
{define-syntax-rule {define/memroize*/forever (f x ...) v}
  {define f
    {let ([h (make-mutable-hash-lazy)])
      {入 (x ...)
        (dict-ref! h `(,x ...) {入 () v})}}}}
{define-syntax-rule {define-rec is? (f p ...)}
  {begin
    {define s (string->symbol (string-append "rec:" (symbol->string 'f)))}
    {define (f p ...) `#(,s ,p ...)}
    {define (is? x) (and (vector? x) (< 0 (vector-length x)) (eq? (vector-ref x 0) s))}
    {define-rec%%hel is? 1 (p ...)}}}
{define-syntax define-rec%%hel
  {syntax-rules ()
    [(_ is? n (p)) {define (p x) (if (is? x) (vector-ref x n) (error))}]
    [(_ is? n (p . ps))
     {begin
       {define (p x) (if (is? x) (vector-ref x n) (error))}
       {define n2 (+ n 1)}
       {define-rec%%hel is? n2 ps}}]}}

{define 等? equal?}

{define :<S集_S陰_S陽>? boolean?}
{define (:S陰? 甲) (等? 甲 其:S陰)}
{define 其:S陰 #f}
{define (:S陽? 甲) (等? 甲 其:S陰)}
{define 其:S陽 #t}
{define <S集_S陰_S陽>.若 if}

{define (:S列? 甲) (or (:S列/連? 甲) (:S列/空? 甲))}
{define :S列/連? pair?}
{define ->S列/連 cons}
{define S列/連.首 car}
{define S列/連.尾 cdr}
{define :S列/空? null?}
{define 其:S列/空 '()}

{define (:S名? 甲) (or (:S名/文? 甲) (:S名/構? 甲))}
{define :S名/文? symbol?}
{define-rec :S名/構? (S名/構 S名/構.:S名 S名/構.:S列)}
;{define/memroize*/forever (→S名/構 :名 :列) (S名/構 :名 :列)}
{define ->S名/構 S名/構}

{define-rec :S表? (S表 S表->)}
;{define 空:S表 (S表 (make-immutable-hash-lazy))}
{define 空:S表 (S表 '())}
{define (S表.增 :表 名 :物) (S表 (dict-set (S表-> :表) 名 :物))}
{define (S表.改 :表 名 :化) (S表 (dict-update (S表-> :表) 名 :化))}
{define (S表.取 :表 名) (dict-ref (S表-> :表) 名)}
{define (S表.含？ :表 名) (dict-has-key? (S表-> :表) 名)}
{define (S表.删 :表 名) (dict-remove (S表-> :表) 名)}
{define (S表->S列 :表) (map {入 (p) (list (car p) (cdr p))} (dict->list (S表-> :表)))}

{define-rec :S集? (S集 S集->)}
{define 空:集 (S集 空:S表)}
{define (S集.增 :集 :物) (S集 (S表.增 (S集-> :集) :物 #t))}
{define (S集.含？ :集 :物) (S表.含？ (S集-> :集) :物)}
{define (S集.删 :集 :物) (S集 (S表.删 (S集-> :集) :物))}
{define (S集->S列 :集) (map S列/連.首 (S表->S列 (S集-> :集)))}
{define (集 . xs)
  (if (null? xs)
      空:集
      (S集.增 (apply 集 (cdr xs)) (car xs)))}

{define-rec :S化? (S化 #%S化.內 S化.形 S化.:S物)}
{define (->S化 形 :物) (S化 #f 形 :物)}

{define-rec :S式? (->S式 S式->)}
{define-rec :S構? (->S構 S構.:S名 S構.:S列)}
{define-rec :S誤? (->S誤 S誤->)}
