#lang lazy
{provide
 等？
 陰 陽 陰-陽.若
 :列/連？ →列/連 列/連.首 列/連.尾 其:列/空
 :名/文？ →名/構 :名/構？ 名/構.:名 名/構.:列
 :表？ 空:表 表.增 表.改 表.取 表.含？ 表.删 表→列
 :化？ →化 #%化.內 #%→化/內 化.形 化.:物
 →式 :式？ →式-1
 →構 →構？ 構.:名 構.:列
 →誤 :誤？ →誤-1
 }
{define 等？ equal?}

{define 陰 #f}
{define 陽 #t}
{define 陰-陽.若 if}

{define :列/連？ pair?}
{define →列/連 cons}
{define 列/連.首 car}
{define 列/連.尾 cdr}
{define 其:列/空 '()}

{define :名/文？ symbol?}
{struct →名/構 (:名 :列)}
{define :名/構？ →名/構?}
{define 名/構.:名 →名/構-:名}
{define 名/構.:列 →名/構-:列}

{define :表？ hash?}
{define 空:表 (hash)}
{define 表.增 hash-set}
{define 表.改 hash-update}
{define 表.取 hash-ref}
{define 表.含？ hash-has-key?}
{define 表.删 hash-remove}
{define (表→列 :表) (map (λ (p) (list (car p) (cdr p))) (hash->list :表))}

{struct 集 (:表)}
{define :集？ 集?}
{define 空:集 (集 空:表)}
{define (集.增 :集 :物) (集 (表.增 (集-:表 :集) :物 #t))}
{define (集.含？ :集 :物) (表.含？ (集-:表 :集) :物)}
{define (集.删 :集 :物) (集 (表.删 (集-:表 :集) :物))}
{define (集→列 :集) (map 列/連.首 (表→列 (集-:表 :集)))}

{struct 化 (內 形 :物)}
{define :化？ 化?}
{define (→化 形 :物) (化 #f 形 :物)}
{define #%化.內 化-內}
{define #%→化/內 化}
{define 化.形 化-形}
{define 化.:物 化-:物}

{struct →式 (:物)}
{define :式？ →式?}
{define →式-1 →式-:物}

{struct →構 (:名 :列)}
{define →構？ →構?}
{define 構.:名 →構-:名}
{define 構.:列 →構-:列}

{struct →誤 (:物)}
{define :誤？ →誤?}
{define →誤-1 →誤-:物}
