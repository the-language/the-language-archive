;;    語
;;    Copyright (C) 2017-2018  Zaoqi

;;    This program is free software: you can redistribute it and/or modify
;;    it under the terms of the GNU Affero General Public License as published
;;    by the Free Software Foundation, either version 3 of the License, or
;;    (at your option) any later version.

;;    This program is distributed in the hope that it will be useful,
;;    but WITHOUT ANY WARRANTY; without even the implied warranty of
;;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;    GNU Affero General Public License for more details.

;;    You should have received a copy of the GNU Affero General Public License
;;    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#lang racket
{require "promise.rkt"}
{require (file "構.rkt")}
{define WIP (delay (error))}

{define 集/定/頂 集/定/空}

{define-syntax APP
  {syntax-rules ()
    [{_ s (f ...) r () ()} r]
    [{_ s (f ...) r ((p? x0) x ...) (v0 v ...)}
     (promise-undelay
      v0
      {λ (x0)
        (if (p? x0)
            {APP s (f ...) r (x ...) (v ...)}
            (誤 (構 {引 誤/界/機} (列 s (列 f ...) {引 x0}))))})]
    [{_ s (f ...) r (x0 x ...) (v0 v ...)}
     {let ([x0 v0])
       {APP s (f ...) r (x ...) (v ...)}}]}}
{define-syntax-rule {定/機%2 形 ...} ({定/機%1 形} ...)}
{define-for-syntax (定/機%0 stx)
  (map {λ (x) (syntax-protect #'t)} (syntax->list stx))}
{define-syntax-rule {定 名 物}
  {set! 集/定/頂 (集/定.增 集/定/頂 {引 名} 物)}}
{define-syntax 定/機
  {λ (stx)
    {syntax-case stx ()
      [{_ (名 形 ...) 物} {syntax-case (map {λ (x) (datum->syntax #f (gensym))} (syntax->list #'(形 ...))) ()
                         [(x ...) (syntax-protect #'{定 名 (#%機-內
                                                          {λ (x ...)
                                                            {APP {引 名} (x ...) 物 (形 ...) (x ...)}}
                                                          {quote (x ...)}
                                                          WIP)})]}]}}}
{define-syntax-rule {定/機* x ...}
  {begin {定/機 . x} ...}}
{define-syntax %L%
  {syntax-rules ()
    [(_ () r) r]
    [(_ (x0 x ...) r) (promise-undelay x0 {λ (x0) {%L% (x ...) r}})]}}
{define-syntax-rule {L ([x v] ...) r} ; Racket的自動縮進導致名字不能長
  {let ([x v] ...) {%L% (x ...) r}}}

{define (非-誤？ 甲) (not (誤？ 甲))}

{定 空 空}
{定 集/定/空 集/定/空}
{定 陰 陰}
{定 陽 陽}
{定 引 (式 (機 '(集/定 物) '物))}
{定 定 WIP}
{定 列 (機 '(列) '列)}
{定 名？ (機 '(物) '((！頂 陰陽.若) ((！頂 名/構？) 物) #t ((！頂 名/文？) 物)))}
{定/機*
 [(等？ 甲 乙) (等？ 甲 乙)]
 
 [(首-尾？ (非-誤？ 物)) (首-尾？ 物)]
 [(首-尾 首 尾) (首-尾 首 尾)]
 [(首-尾.首 (首-尾？ 物)) (首-尾.首 物)]
 [(首-尾.尾 (首-尾？ 物)) (首-尾.尾 物)]
 [(空？ (非-誤？ 物)) (空？ 物)]

 [(文？ (非-誤？ 物)) (文？ 物)]

 [(名/文？ (非-誤？ 物)) (名/文？ 物)]
 [(名/文 物) (名/文 物)]
 [(名/文-1 (名/文？ 物)) (名/文-1 物)]
 [(名/構？ (非-誤？ 物)) (名/構？ 物)]
 [(名/構 名 列) (名/構 名 列)]
 [(名/構.名 (名/構？ 物)) (名/構.名 物)]
 [(名/構.列 (名/構？ 物)) (名/構.列 物)]

 [(集/定？ (非-誤？ 物)) (集/定？ 物)]
 [(集/定.增 (集/定？ 物) ({λ (甲) (not (集/定.含？ 物 甲))} 名) 物) (集/定.增 物 名 物)]
 [(集/定.改 (集/定？ 物) ({λ (甲) (集/定.含？ 物 甲)} 名) 者) WIP]
 [(集/定.增-改 (集/定？ 物) 名 物) (集/定.增-改 物 名 物)]
 [(集/定.取 (集/定？ 物) 名) (集/定.取 物 名)]
 [(集/定.含？ (集/定？ 物) 名) (集/定.含？ 物 名)]
 [(集/定.删 (集/定？ 物) ({λ (甲) (集/定.含？ 物 甲)} 名)) (集/定.删 物 名)]
 [(集/定→列 (集/定？ 物)) (集/定→列 物)]

 [(機？ (非-誤？ 物)) (機？ 物)]
 [(機 形 物) (機 形 物)]
 [(機.用 (機？ 物) 形) (機.用 物 形)]
 [(機.形 (機？ 物)) (機.形 物)]
 [(機.物 (機？ 物)) WIP]

 [(陰陽.若 (陰-陽？ 物) 甲 乙) (if 物 甲 乙)]

 [(式？ (非-誤？ 物)) (式？ 物)]
 [(式 機) (式 機)]
 [(式-1 (式？ 物)) (式-1 物)]
 
 [(誤？ (非-誤？ 物)) (誤？ 物)]
 [(誤 物) (誤 物)]
 [(誤-1 (誤？ 物)) (誤-1 物)]

 [(算 物 (集/定？ 集/定)) (算 物 集/定)]

 [(構？ (非-誤？ 物)) (構？ 物)]
 [(構 名 列) (構 名 列)]
 [(構.名 (構？ 物)) (構.名 物)]
 [(構.列 (構？ 物)) (構.列 物)]

 [(取 名) WIP]}
{定 集/定/頂 集/定/頂}

{define (機.用 機 形)
  WIP
  }
{define (算 物 集/定)
  {define E (delay (誤 (構 {引 誤/界/機} (列 {引 算} (列 物 集/定) {引 物}))))}
  (delay
    {L ([物 物])
       {cond
         [(首-尾？ 物)
          {L ([首 (首-尾.首 物)] [尾 (首-尾.尾 物)])
             {if (首-尾？ 尾)
                 {L ([尾@首 (首-尾.首 尾)] [尾@尾 (首-尾.尾 尾)])
                    {cond
                      [(等？ 首 {引 ！式}) WIP]
                      [(等？ 首 {引 ！頂})
                       (if (空？ 尾@尾)
                           (集/定.取 集/定/頂 物 (delay (誤 (構 {引 誤/界/名} (列 物 集/定/頂)))))
                           E)]
                      [else WIP]}}
                 E}}]
         [(名？ 物) (集/定.取 集/定 物 (delay (誤 (構 {引 誤/界/名} (列 物 集/定)))))]
         [else 物]}})}
