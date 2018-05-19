#lang racket
{require (file "cons.rkt")}
{provide 引}

{define 其:類 (→構 (→名/構 '子 '(類 其)) '())}
{define 類/化 (→名/構 '子 '(類 化))}
{define 類/列 (→名/構 '子 '(類 列))}
{define 類/列/連 (→名/構 '子 `(,類/列 連))}
{define 類/集 (→名/構 '子 '(類 集))}
{define 類/名 (→名/構 '子 '(類 名))}
{define 類/列/空:類 (→構 (→名/構 '子 `(,類/列 空)) '())}
{define (symbol→名 sym) (list→名 (string->list (symbol->string sym)))}
{define list→名
  {match-lambda
    [(list #\# #\% 甲 ..1) (→名/構 '式 (list (list→名 甲)))]
    [(list 類 ..1 #\. 名 ..1 (or #\？ #\?)) "WIP"]
    [(list 類 ..1 #\. 名 ..1) "WIP"]
    [(list #\: 甲 ..1 (or #\？ #\?)) "WIP"]
    [(list 甲 ..1 (or #\？ #\?))
     (→名/構 '一 (list
               (→構 類/化 (list 其:類 "WIP"))
               '其))]
    [(list 甲 ..1 #\: 乙 ..1) (→名/構 '一 (list (list→type 乙) (list→名 甲)))]
    [(list #\: 甲 ..1) (→名/構 '一 (list (list→type 甲)))]
    [(or (list 甲 ..1 #\→ 乙 ..1) (list 甲 ..1 #\- #\> 乙 ..1))
     (→名/構 '一 (list
               (→構 類/化 (list (→構 類/列/連 (list (list→type 甲) 類/列/空:類)) (list→type 乙)))
               '其))]
    [(or (list #\→ 甲 ..1) (list #\- #\> 甲 ..1))
     (→名/構 '一 (list
               (→構 類/化 (list 其:類 (list→type 甲)))
               '其))]
    [(or (list 甲 ..1 #\→) (list 甲 ..1 #\- #\>))
     (→名/構 '一 (list
               (→構 類/化 (list (→構 類/列/連 (list (list→type 甲) 類/列/空:類)) 其:類))
               '其))]
    [甲 (string->symbol (list->string 甲))]
    }}
{define list→type
  ({λ ()
     {define 二其 (list 其:類 其:類)}
     {define 一其 (list 其:類)}
     {define 陰 (→構 (→名/構 '子 '(類 陰)) '())}
     {define 陽 (→構 (→名/構 '子 '(類 陽)) '())}
     {define 連 (→構 類/列/連 二其)}
     {define 名/文 (→構 (→名/構 '子 `(,類/名 文)) '())}
     {define 名/構 (→構 (→名/構 '子 `(,類/名 構)) 二其)}
     {define 物 (→構 (→名/構 '子 '(類 物)) '())}
     {define 表 (→構 (→名/構 '子 '(類 表)) 二其)}
     {define 集 (→構 (→名/構 '子 '(類 表)) 一其)}
     {define 化 (→構 類/化 二其)}
     {define 式 (→構 (→名/構 '子 '(類 式)) 一其)}
     {define 構 (→構 (→名/構 '子 '(類 構)) 二其)}
     {define 誤 (→構 (→名/構 '子 '(類 誤)) 一其)}
     {define list→type
       {match-lambda
         ['(#\物) 物]
         ['(#\陰) 陰]
         ['(#\陽) 陽]
         ['(#\列 #\/ #\連) 連]
         ['(#\列 #\/ #\空) 類/列/空:類]
         ['(#\名 #\/ #\文) 名/文]
         ['(#\名 #\/ #\構) 名/構]
         ['(#\表) 表]
         ['(#\集) 集]
         ['(#\化) 化]
         ['(#\式) 式]
         ['(#\構) 構]
         ['(#\誤) 誤]
         [甲 (→構 (→名/構 '子 '(類 構)) (list (list→名 甲) 其:類))]
         }}
     list→type})}
{define-syntax-rule {引 x} (symbol→名 'x)}
