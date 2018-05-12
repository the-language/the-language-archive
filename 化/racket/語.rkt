#lang lazy
{require (file "cons.rkt")}

{define WIP WIP}

{define (算 :物 :表)
  (陰-陽.若 (:名？ :物)
         (hash-ref :表 :物 WIP)
         (陰-陽.若 (:列/連？ :物)
                {let ([首 (列/連.首 :物)] [尾 (列/連.尾 :物)])
                  (陰-陽.若 (list? 尾)
                         (化.用 (算 首 :表) (map (λ (x) (算 x :表)) 尾))
                         WIP)}
                WIP))}
{define (化.用 :化 形)
  WIP}