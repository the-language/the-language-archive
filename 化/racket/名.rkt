#lang racket
{require (file "cons.rkt")}
{provide 引}

{define 其:type (→構 (→名/構 '子 '(類 其)) '())}
{define (symbol→名 sym) (list→名 (string->list (symbol->string sym)))}
{define list→名
  {match-lambda
    [(list #\# #\% 甲 ..1) (→名/構 '式 (list (list→名 甲)))]
    [(list 甲 ..1 (or #\？ #\?)) "WIP"]
    [(list 甲 ..1 #\: 乙 ..1) (→名/構 '一 (list (list→type 乙) (list→名 甲)))]
    [(list #\: 甲 ..1) (→名/構 '一 (list (list→type 甲)))]
    [(or (list 甲 ..1 #\→ 乙 ..1) (list 甲 ..1 #\- #\> 乙 ..1)) ("WIP" (list→type 甲) (list→type 乙))]
    [(or (list #\→ 甲 ..1) (list #\- #\> 甲 ..1)) (→名/構 '一 (list
                                                          (→構 (→名/構 '子 '(類 化)) (list (→列/連 (list→type 甲) 其:type) 其:type))
                                                          '其))]
    [(or (list 甲 ..1 #\→) (list 甲 ..1 #\- #\>)) ("WIP" (list→type 甲))]
    [甲 (string->symbol (list->string 甲))]
    }}
{define list→type
  ({λ ()
     {define 二其 (list 其:type 其:type)}
     {define 一其 (list 其:type)}
     {define 陰 (→構 (→名/構 '子 '(類 陰)) '())}
     {define 陽 (→構 (→名/構 '子 '(類 陽)) '())}
     {define 連 (→構 (→名/構 '子 '(類 列 連)) 二其)}
     {define 空 (→構 (→名/構 '子 '(類 列 空)) '())}
     {define 文 (→構 (→名/構 '子 '(類 名 文)) '())}
     {define 名/構 (→構 (→名/構 '子 '(類 名 構)) 二其)}
     {define 物 (→構 (→名/構 '子 '(類 物)) '())}
     {define 表 (→構 (→名/構 '子 '(類 表)) 二其)}
     {define 集 (→構 (→名/構 '子 '(類 表)) 一其)}
     {define 化 (→構 (→名/構 '子 '(類 化)) 二其)}
     {define 式 (→構 (→名/構 '子 '(類 式)) 一其)}
     {define 構 (→構 (→名/構 '子 '(類 構)) 二其)}
     {define 誤 (→構 (→名/構 '子 '(類 誤)) 一其)}
     {define list→type
       {match-lambda
         ['(#\物) 物]
         ['(#\陰) 陰]
         ['(#\陽) 陽]
         ['(#\列 #\/ #\連) 連]
         ['(#\列 #\/ #\空) 空]
         ['(#\名 #\/ #\文) 文]
         ['(#\名 #\/ #\構) 名/構]
         ['(#\表) 表]
         ['(#\集) 集]
         ['(#\化) 化]
         ['(#\式) 式]
         ['(#\構) 構]
         ['(#\誤) 誤]
         [甲 (→構 (→名/構 '子 '(類 構)) (list (list→名 甲) 其:type))]
         }}
     list→type})}
{define-syntax-rule {引 x} (symbol→名 'x)}
