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
{require (file "構.rkt")}
{define WIP (delay (error))}
{define (undelay x f)
  {cond
    [(promise? x)
     (if (promise-forced? x)
         (undelay (force x) f)
         (delay (undelay (force x) f)))]
    [else (f x)]}}

{define 境/空 映/空}

{define-syntax APP
  {syntax-rules ()
    [{_ e r () ()} r]
    [{_ e r ((p? x0) x ...) (v0 v ...)}
     (undelay v0
              {λ (x0)
                (if (p? x0)
                    {APP e r (x ...) (v ...)}
                    e)})]
    [{_ e r (x0 x ...) (v0 v ...)}
     {let ([x0 v0])
       {APP e r (x ...) (v ...)}}]}}
{define-syntax 定/機%1
  {syntax-rules ()
    [{_ (p? x0)} x0]
    [{_ x0} x0]}}
{define-syntax-rule {定/機%2 形 ...} ({定/機%1 形} ...)}
{define-syntax-rule {定 名 物}
  {set! 境/空 (映.增 境/空 (symbol→名 {quote 名}) 物)}}
{define-syntax-rule {定/機 (名 形 ...) 物}
  {定 名 (#%機-內
              {λ {定/機%2 形 ...}
                {APP WIP 物 (形 ...) {定/機%2 形 ...}}}
              {quote {定/機%2 形 ...}}
              WIP)}}
{define-syntax-rule {定/機* x ...}
  {begin {定/機 . x} ...}}

{定 空 空}
{定 列 WIP}
{定 映/空 映/空}
{定/機*
 [(等？ 甲 乙) (等？ 甲 乙)]
 
 [(首-尾？ 甲) (undelay 甲 首-尾？)]
 [(首-尾 首 尾) (首-尾 首 尾)]
 [(首-尾.首 (首尾？ 首)) (首-尾.首 首)]
 [(首-尾.尾 (首尾？ 首)) (首-尾.尾 首)]
 [(空？ 甲) (undelay 甲 空？)]

 [(文？ 甲) (undelay 甲 文？)]

 [(名/文？ 甲) (undelay 甲 名/文？)]
 [(名/文 列) (名/文 列)]
 [(名/文-1 (名/文？ 甲)) (名/文-1 甲)]
 [(名/構？ 甲) (undelay 甲 名/構？)]
 [(名/構 名 列) (名/構 名 列)]
 [(名/構.名 (名/構？ 甲)) (名/構.名 甲)]
 [(名/構.列 (名/構？ 甲)) (名/構.列 甲)]
 [(名？ 甲) (undelay 甲 名？)]

 [(映？ 甲) (undelay 甲 映？)]
 [(映.增 (映？ 映) ({λ (甲) (not (映.含？ 映 甲))} 名) 物) (映.增 映 名 物)]
 [(映.改 (映？ 映) ({λ (甲) (映.含？ 映 甲)} 名) 者) WIP]
 [(映.增-改 (映？ 映) 名 物) (映.增-改 名 物)]
 [(映.取 (映？ 映) 名) (映.取 映 名)]
 [(映.含？ (映？ 映) 名) (映.含？ 映 名)]
 [(映.删 (映？ 映) ({
