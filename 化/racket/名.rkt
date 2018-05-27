#lang racket
{require (file "cons.rkt")}

{define list->名
  {match-lambda
    [(list #\# #\% 甲 ...) (名.構.建+ '式 `(,(list->名 甲)))]
    ['WIP 'WIP]
    [甲 (string->symbol (list->string 甲))]
    }}
