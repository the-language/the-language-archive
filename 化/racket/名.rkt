#lang racket
{require (file "cons.rkt")}
{provide 引}

{define (symbol→名 sym) (list→名 (string->list (symbol->string sym)))}
{define list→名
  {match-lambda
    [(list #\# #\% 甲 ...) (→名/構 '式 (list (list→名 甲)))]
    [(list 甲 ... #\: 乙 ...) (→名/構 '一 (list (list→type 乙) (list→名 甲)))]
    [(list #\: 甲 ...) (→名/構 '一 (list (list→type 甲)))]
    }}
{define list→type
  {match-lambda
    }}
{define-syntax-rule {引 x} (symbol→名 'x)}
