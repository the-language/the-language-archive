#lang scribble/manual
@require[@for-label[racket]]

@title{語}
@author{zaoqi}

@defmodule[zaoqil #:lang]

@define-syntax-rule[(重名詞法 名 原) @define-syntax-rule[(名 . 參) (原 . 參)]]

@重名詞法[述機 defproc]
@重名詞法[語 racket]
@重名詞法[述 defform]
@重名詞法[述/子 defform/subs]
@重名詞法[述值 defthing]

這裏不使用racket語法

@述機[(等？ [甲 物？] [乙 物？]) 陰陽？]{返回@語[甲]是否等於@語[乙]。}

@述機[(首尾？ [甲 物？]) 陰陽？]{返回@語[甲]是否是@語[(首尾 之首 之尾)]。}
@述機[(首尾 [首 物？] [尾 物？]) 首尾？]
@述機[(首尾-首 [甲 首尾？]) 物？]{若@語[甲]是@語[(首尾 之首 之尾)]，返回@語[之首]。}
@述機[(首尾-尾 [甲 首尾？]) 物？]{若@語[甲]是@語[(首尾 之首 之尾)]，返回@語[之尾]。}
@述機[(空？[甲 物？]) 陰陽？]{返回@語[甲]是否是@語[()]。}
@述值[列 機？ #:value [入 甲 甲]]

@述機[(字？ [甲 物？]) 陰陽？]{返回@語[甲]是否是字符。}

@述機[(名？ [甲 值？]) 陰陽？]{返回@語[甲]是否是@語[(名 列)]。}
@述機[(列→名 [列 列？]) 名？]{例子：@語[[引 符號]]是@語[(名 (列→名 (列 (列 ；符 ；號))))]。}
@述機[(名→列 [甲 名？]) 列？]{若@語[甲]是@語[(名 列)]，返回@語[列]。}

@述機[(映？ [甲 物？]) 陰陽？]
@述值[映-空 映？]{空映射。}
@述機[(映-改 [映 映？] [名 物？] [物 物？]) 映？]{返回創建或修改了的映射。}
@述機[(映-取 [映 映？] [名 物？]) 物？]
@述機[(映-含？ [映 映？] [名 物？]) 陰陽？]
@述機[(映-删 [映 映？] [名 物？]) 映？]
@述機[(映→列 [映 映？]) (listof (cons/c any/c any/c))]

@述[(！-式 甲 ...)]{使用一個@語[引機？]或@語[譯機？]。可以寫作@語[[甲 ...]]。}

@述機[(機？ [甲 物？]) 陰陽？]
@述機[(機 [形 物？] [物 未算？]) 機？]
@述機[(用 [機 機？] [形 列？]) 物？]{用@語[形]應用@語[機]。}
@述機[(機-形 [機 機？]) 物？]{
 若@語[機]是@語[[入 形 物]]，返回@語[[引 -形]]。
 @語[-形]和@語[形]等價。
 @語[機-形]是純函數。
}
@述機[(機-物 [-機 機？]) 未算？]{
 @語[-形]是@語[(機-形 -機)]。
 @語[-機]和
 @語[[入 -形
     (算 (機-式 -機) -境)]]等價。
 @語[-境]是只包含@語[-形]的環境。
}
@述/子[[入 形 物]
     ([形 (甲 ...)
       (甲 ...+ . 之尾)
       甲])]{
 返回一個@語[機？]。
}

@述值[陰 陰陽？]
@述值[陽 陰陽？]
@述機[(若 [甲 物？] [乙 物？] [丙 物？]) 物？]{若@語[甲]是@語[陽]，則返回@語[乙]，否則返回@語[丙]。}

@述機[(引機？ [甲 物？]) 陰陽？]
@述機[(引機 [機 (-> 映？ 未算？ ... 物？)]) 引機？]
@述機[(引機-反 [甲 引機？]) (-> 映？ 未算？ ... 物？)]{@語[引機]的反函數。}

@述機[(譯機？ [甲 物？]) 陰陽？]
@述機[(譯機 [機 (-> 未算？ ... 未算？)]) 譯機？]
@述機[(譯機-反 [甲 引機引？]) (-> 未算？ ... 未算？)]{@語[譯機]的反函數。}

@述值[引 引機？ #:value (引機 [入 (境 物) 物])]

@述[(！-界 名)]{空境中的值。內置的值。}

@述機[(誤？ [甲 值？]) 陰陽？]
@述機[(誤 [甲 值？]) 誤？]{
 內置的函數可以產生@語[(誤 (構 (列→名 (列 [引 界] [引 誤] [引 -名])) -列))]。
 @語[-名]是函數的名字。
 @語[-列]一般是參數。}
@述機[(誤-反 [甲 誤？]) 物？]

@述機[(算 [未算 未算？] [境 映？]) 物？]

@述[[境-名今 名 物]]{把現在的環境命名爲@語[名]，返回@語[物]。}
@述[[境-改 新境 物]]
@述值[境-空 映？]

@述[[命名 ((標識符 之物) ...) 物]]{@racket[letrec]}

@述機[(構？ [甲 物？]) 陰陽？]{返回@語[甲]是否是@語[(構 名 列)]。}
@述機[(構 [名 名？] [列 列？]) 構？]
@述機[(構-名 [甲 構？]) 物？]{若@語[甲]是@語[(構 名 列)]，返回@語[名]。}
@述機[(構-列 [甲 構？]) 物？]{若@語[甲]是@語[(構 名 列)]，返回@語[列]。}

@述機[(取-未算 [名 名？]) 未算？]{獲取一個包}
@述值[取 機？ #:value [入 (名) (算 (取-未算 名) 境-空)]]

@述機[(界-含？ [名 物？]) 陰陽？]{返回運行這個程序的世界是否支持@語[名]。}
@述機[(界-取 [名 物？]) 物？]
