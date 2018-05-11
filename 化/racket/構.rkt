#lang lazy
{provide
 等？
 陰 陽 陰-陽.若
 :列/連？ →列/連 列/連.首 列/連.尾 其:列/空
 :名/文？ →名/構 :名/構？ 名/構.:名 名/構.:列
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