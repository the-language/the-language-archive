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
{define-syntax-rule {定/機 (名 形 ...) 物}
  {set! 境/空 (映.增
             境/空 (symbol→名 名)
             (#%機-內
              {λ {定/機%2 形 ...}
                {APP WIP 物 (形 ...) {定/機%2 形 ...}}}
              {quote {定/機%2 形 ...}}
              WIP))}}
