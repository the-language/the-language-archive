#lang racket
{require (file "cons.rkt")}

{define #%頂 (名.構.建+ '式 '(頂))}
{define #%式 (名.構.建+ '式 '(式))}
{define 之+ (名.構.建+ '一 '(化 之))}
{define !引 (名.構.建+ '一 '(式 引))}
{define #%頂-之+ (列.建+ #%頂 之+)}
{define #%頂-!引 (列.建+ #%頂 !引)}
{define (引 甲) (列.建+ #%式 #%頂-!引 甲)}
{define (S 甲) (string->symbol (list->string 甲))}

{define list->未算
  {match-lambda
    [(list #\# #\% 甲 ...) (名.構.建+ '式 `(,(list->未算 甲)))]
    [(list 甲 ... #\. (and 乙 (not #\.)) ...) (列.建+ #%頂-之+ (list->未算 甲) (引 (S 乙)))]
    ['WIP 'WIP]
    [甲 (S 甲)]
    }}
