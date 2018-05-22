#lang lazy
{require (file "cons.rkt")}

{define (子 甲 乙) (→名/構 '子 `(,甲 ，乙))}
{define (一 . xs) (→名/構 '一 xs)}

{define 物:類 (→構 (子 '類 '物) '())}

{define 類/列/連 (子 '類 (子 '列 '連))}

{define 類/集 (子 '類 '集)}
{define 集:類 (→構 類/集 `(,物:類))}

{define 類/:集 (子 '類 (一 集:類))}

{define 類/名/文 (子 '類 (子 '名 '文))}