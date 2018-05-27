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

{define (symbol->未算 s) (string->未算 (symbol->string s))}
{define (string->未算 s) (list->未算 (string->list s))}
{define list->未算
  {match-lambda
    [(list #\# #\% 甲 ..1) (名.構.建+ '式 `(,(list->未算 甲)))]
    [(list 甲 ..1 #\. (and 乙 (not #\.)) ..1) (列.建+ #%頂-之+ (list->未算 甲) (引 (list->未算 乙)))]
    [(list 甲 ..1 #\: 乙 ..1) (名.構.建+ '一 `(,(list->未算 乙) ,(list->未算 甲)))]
    [(list #\: 乙 ..1) (名.構.建+ '一 `(,(list->未算 乙)))]
    [(list (or #\? #\？)) '乎]
    [(list #\< (and 甲 (not #\>)) ..1 #\>) (集->未算 甲)]
    [(list 甲 ..1 (or #\? #\？)) (名.構.建+ '乎 `(,(list->未算 甲)))]
    [(list 甲 ..1 #\+) (名.構.建+ '一 `(化 ,(list->未算 甲)))]
    [(list (or #\! #\！) 甲 ..1) (名.構.建+ '一 `(式 ,(list->未算 甲)))]
    ['WIP 'WIP]
    [甲 (S 甲)]
    }}
{define (集->未算 甲) (名.構.建+ '集 `(,(#%集->未算 甲)))}
{define #%集->未算
  {match-lambda
    [(list (and 甲 (not (or #\, #\，))) ..1 (or #\, #\，) 乙 ..1) (集.增+ (#%集->未算 乙) (list->未算 甲))]
    [甲 (集.建+ (S 甲))]}}
