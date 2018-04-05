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
(provide promise? set-promise! delay promise-running? promise-forced? promise-undelay)

(struct #%promise (p) #:transparent)
(struct #%promise-running () #:transparent)
(struct #%promise-undelaying (x p) #:transparent)
(struct promise ((x #:mutable)) #:transparent)

(define set-promise! set-promise-x!)
(define (promise-undelay x f) (promise (#%promise-undelaying x f)))

(define-syntax-rule (delay body ...) (promise (#%promise (λ () body ...))))

(define (force v)
  (if (promise? v)
      (#%force (promise-x v) (list v) v)
      v))
(define (#%force x promise-list a-promise)
  (cond
    [(#%promise-running? x) (error 'force "reentrant promise")] ; BUG 若有multi thread
    [(promise? x) (#%force (promise-x x) (cons x promise-list) a-promise)]
    [(#%promise-undelaying? x)
     (let ([t (force (#%promise-undelaying-x x))] [p (#%promise-undelaying-p x)])
       (if (promise? t)
           (#%force-end a-promise (#%promise-undelaying t p) promise-list)
           (let ([r (p t)]) (#%force-end r r promise-list))))]
    [(#%promise? x) (let ([r ((#%promise-p x))]) (#%force-end r r promise-list))]
    [else (#%force-end x x promise-list)]))
(define (#%force-end r v xs)
  (if (null? xs)
      r
      (begin
        (set-promise! (car xs) v)
        (#%force-end r v (cdr xs)))))
(define (promise-running? x) (#%promise-running?0 (promise-x x) (list x)))
(define (#%promise-running?0 x promise-list)
  (cond
    [(#%promise-running? x) (#%force-end #t x promise-list)]
    [(promise? x) (#%promise-running?0 (promise-x x) (cons x promise-list))]
    [else (#%force-end #f x promise-list)]))
(define (promise-forced? x) (#%promise-forced? (promise-x x) (list x)))
(define (#%promise-forced? x promise-list)
  (cond
    [(or (#%promise? x) (#%promise-running? x) (#%promise-undelaying? x)) (#%force-end #f x promise-list)]
    [(promise? x) (#%promise-forced? (promise-x x) (cons x promise-list))]
    [else (#%force-end #t x promise-list)]))
