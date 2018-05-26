#lang racket
{provide define-rec}
{define-syntax-rule {define-rec is? (f p ...)}
  {begin
    {define s (string->symbol (string-append "rec:" (symbol->string 'f)))}
    {define (f p ...) `#(,s ,p ...)}
    {define (is? x) (and (vector? x) (< 0 (vector-length x)) (eq? (vector-ref x 0) s))}
    {hel is? 1 (p ...)}}}
{define-syntax hel
  {syntax-rules ()
    [(_ is? n (p)) {define (p x) (if (is? x) (vector-ref x n) (error))}]
    [(_ is? n (p . ps))
     {begin
       {define (p x) (if (is? x) (vector-ref x n) (error))}
       {define n2 (+ n 1)}
       {hel is? n2 ps}}]}}
