#lang racket
{require (file "cons.rkt")}
{provide 引}

{define (symbol→名 sym) (list→名 (string->list (symbol->string sym)))}
{define list→名
  {match-lambda
    [(list #\# #\% 甲 ..1) (→名/構 '式 (list (list→名 甲)))]
    [(list 甲 ..1 (or #\？ #\?)) "WIP"]
    [(list 甲 ..1 #\: 乙 ..1) (→名/構 '一 (list (list→type 乙) (list→名 甲)))]
    [(list #\: 甲 ..1) (→名/構 '一 (list (list→type 甲)))]
    [(or (list 甲 ..1 #\→ 乙 ..1) (list 甲 ..1 #\- #\> 乙 ..1)) ("WIP" (list→type 甲) (list→type 乙))]
    [(or (list #\→ 甲 ..1) (list #\- #\> 甲 ..1)) ("WIP" (list→type 甲))]
    [(or (list 甲 ..1 #\→) (list 甲 ..1 #\- #\>)) ("WIP" (list→type 甲))]
    }}
{define list→type
  ({λ ()
     {define 其:type (→構 (→名/構 '子 '(類 其) '()))}
     {define 陰 (→構 (→名/構 '子 '(類 陰)) '())}
     {define 陽 (→構 (→名/構 '子 '(類 陽)) '())}
     {define 連 (→構 (→名/構 '子 '(類 列 連)) (list 其:type 其:type))}
     {define 空 (→構 (→名/構 '子 '(類 列 空)) '())}
     {define list→type
       {match-lambda
         [(list #\陰) 陰]
         [(list #\陽) 陽]
         [(list #\列 #\/ #\連) 連]
         [(list #\列 #\/ #\空) 空]
         }}
     list→type})}
{define-syntax-rule {引 x} (symbol→名 'x)}
