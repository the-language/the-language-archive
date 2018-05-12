#lang lazy
{require (file "cons.rkt")}
{require (file "名.rkt")}

{define WIP "WIP"}

{define 頂:表 WIP}

{define (算 :物 :表)
  {cond
    [(:名？ :物) (hash-ref :表 :物 WIP)]
    [(and (list? :物) (:列/連？ :物))
     {let ([首 (列/連.首 :物)] [尾 (列/連.尾 :物)])
       (cond
         [(等？ 首 {引 #%頂})
          (陰-陽.若 (and (= (length 尾) 1) (表.含？ 頂:表 (列/連.首 尾)))
                 (表.取 頂:表 (列/連.首 尾))
                 WIP)]
         [(等？ 首 {引 #%式}) WIP]
         [else (化.用 (算 首 :表) (map (λ (x) (算 x :表)) 尾))])}]
    [else WIP]}}
{define (化.用 :化 形)
  WIP}