語
==
    The Language: the best programming language
    Copyright (C) 2014-2018  Zaoqi <zaomir@outlook.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

化
--
[HTML](http://xn--2e3a.ml/)
# 語

zaoqi

```racket
 #lang lang package: [lang](https://pkgs.racket-lang.org/package/lang)
```

## 1. 形式

```racket
(#%式 式 甲 ...)
```

等價與使用`化.用+`和`式.建+-1`。使用一個`式.？式`。可以寫作`{式 甲 ...}`。

```racket
頂:表 : 表.？
```

```racket
(#%頂 名)
```

頂層的物。

```racket
(化 形 ...)
```

等價與使用`化.用+`。

## 2. 物

### 2.1. 結構/值

#### 2.1.1. 結構/值 化

`(化.建+ '<形> '((#%頂 <名>) . <形>))`

### 2.2. 述

```racket
(等？ 甲 乙) -> <陰，陽>.？
  甲 : (非 誤.？)      
  乙 : (非 誤.？)      
```

返回`甲`是否等於`乙`。

```racket
(算+ :物 :表) -> 物.？
  :物 : 物.？       
  :表 : 表.？       
```

```racket
(取+ :名) -> 物.？
  :名 : 名？     
```

獲取一個包

```racket
(或+ 甲 乙) -> 物.？
  甲 : 物.？      
  乙 : 物.？      
```

一般是`甲`，可以是`乙`。

```racket
!引 : 式.？ = (式.建+ (化.建+ '(:表 :物) ':物))
```

#### 2.2.1. 陰-陽

```racket
<陰，陽>.陰.其 : <陰，陽>.陰.？
```

```racket
<陰，陽>.陽.其 : <陰，陽>.陽.？
```

```racket
(<陰，陽>.若+ :<陰，陽> 甲 乙) -> 物.？
  :<陰，陽> : <陰，陽>.？          
  甲 : 物.？                   
  乙 : 物.？                   
```

若`:<陰，陽>`是`<陰，陽>.陽.其`，則返回`乙`，否則返回`丙`。

#### 2.2.2. 列

```racket
(列.連.？ :物) -> <陰，陽>.？
  :物 : (非 誤.？)       
```

```racket
(列.連.建+ 首 尾) -> :列/構？
  首 : 物.？            
  尾 : 物.？            
```

```racket
(列.連.首+ :列/連) -> 物.？
  :列/連 : 列.連.？      
```

```racket
(列.連.尾+ :列/連) -> 物.？
  :列/連 : 列.連.？      
```

```racket
列.空.其 : 列.空.？ = ()
```

#### 2.2.3. 名

```racket
(名.文.？ :物) -> <陰，陽>.？
  :物 : (非 誤.？)       
```

```racket
(名.構.？ :物) -> <陰，陽>.？
  :物 : (非 誤.？)       
```

```racket
(名.構.建+ :名 :列) -> 名.構.？
  :名 : 物.？             
  :列 : 物.？             
```

`:名`一般是`:名`。`:列`一般是`:列`。

```racket
(名.構.:名++ :名/構) -> 物.？
  :名/構 : 名.構.？        
```

```racket
(名.構.:列++ :名/構) -> 物.？
  :名/構 : 名.構.？        
```

#### 2.2.4. 表

```racket
(表.？ :物) -> <陰，陽>.？
  :物 : (非 誤.？)     
```

```racket
表.空 : 表.？
```

```racket
(表.增+ :表 名 :物) -> 表.？
  :表 : 表.？           
  名 : 物.？            
  :物 : 物.？           
```

原來沒有，是增。

```racket
(表.改+ :表 名 :化) -> 表.？
  :表 : 表.？           
  名 : 物.？            
  :化 : (-> 物.？ 物.？)  
```

```racket
(表.取+ :表 名) -> 物.？
  :表 : 表.？        
  名 : 物.？         
```

```racket
(表.含？ :表 名) -> <陰，陽>.？
  :表 : 表.？            
  名 : 物.？             
```

```racket
(表.删+ :表 名) -> 表.？
  :表 : 表.？        
  名 : 物.？         
```

必須有，才能刪。

```racket
(表.→列 :表) -> (listof (list/c any/c any/c))
  :表 : 表.？                                
```

#### 2.2.5. 集

```racket
(集.？ :物) -> <陰，陽>.？
  :物 : (非 誤.？)     
```

```racket
集.空 : 集.？
```

```racket
(集.增+ :集 :物) -> 集.？
  :集 : 集.？         
  :物 : 物.？         
```

原來沒有，是增。

```racket
(集.含？ :集 :物) -> <陰，陽>.？
  :集 : 集.？             
  :物 : 物.？             
```

```racket
(集.删+ :集 :物) -> 集.？
  :集 : 集.？         
  :物 : 物.？         
```

必須有，才能刪。

```racket
(集.→列 :集) -> (listof any/c)
  :集 : 集.？                 
```

#### 2.2.6. 化

```racket
(化.？ :物) -> <陰，陽>.？
  :物 : (非 誤.？)     
```

```racket
(化.建+ 形 :物) -> 化.？
  形 : 物.？         
  :物 : 物.？        
```

`形`類似Scheme，不是`:列`的當成`symbol?`。

```racket
(化.形+ :化) -> 物.？
  :化 : 化.？      
```

```racket
(化.:物+ :化) -> 物.？
  :化 : 化.？       
```

```racket
(化.用+ :化 形) -> 物.？
  :化 : 化.？        
  形 : 物.？         
```

如果`形`和`:物`不能匹配，這個`:誤`是`形`產生的。

#### 2.2.7. 式

```racket
(式.？ :物) -> <陰，陽>.？
  :物 : (非 誤.？)     
```

```racket
(式.建+ :化) -> 式.？
  :化 : 物.？      
```

`化`一般是`(-> 表.？ 物.？ ... 物.？)`。

```racket
(式.反+ :式) -> 物.？
  :式 : 式.？      
```

#### 2.2.8. 構

```racket
(構.？ :物) -> <陰，陽>.？
  :物 : (非 誤.？)     
```

```racket
(構.建+ :名 :列) -> 構.？
  :名 : 物.？         
  :列 : 物.？         
```

`:名`一般是`:名`，`:列`一般是`:列`。

```racket
(構.:名+ :構) -> 物.？
  :構 : 構.？       
```

```racket
(構.:列+ :構) -> 物.？
  :構 : 構.？       
```

#### 2.2.9. 誤

```racket
(誤.？ :物) -> <陰，陽>.？
  :物 : 物.？         
```

```racket
(誤.建+ :物) -> 誤.？
  :物 : 物.？      
```

```racket
(誤.反+ :誤) -> 物.？
  :誤 : 誤.？      
```

## 3. 誤

### 3.1. 無

替換：在進行0或更多次替換後，可以把沒有結果（需要無限的時間的）的任意個`:物`替換爲`(誤.建+ (構.建+ {!引 誤/界/無}
<未定義>))`，`<未定義>`是任意的`:物`。

實現應該儘量避免無限的運行下去。

實現應該儘量避免無用的替換。

### 3.2. 化

內置的任何`:化`產生的`:誤`是`(誤.建+ (構.建+ {!引 誤/界/化} ((化.建+ '(:列) ':列) <:名> <式>
<位:名>)))`， `<:名>`是它的名稱，`<式>`是它的參數，`<位:名>`是產生`:誤`的參數的名稱。

## 4. 類Racket語法

每個vector和symbol會被轉換爲一個`:名`。

WIP
