--    Copyright (C) 2018  Zaoqi

--    This program is free software: you can redistribute it and/or modify
--    it under the terms of the GNU Affero General Public License as published
--    by the Free Software Foundation, either version 3 of the License, or
--    (at your option) any later version.

--    This program is distributed in the hope that it will be useful,
--    but WITHOUT ANY WARRANTY; without even the implied warranty of
--    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--    GNU Affero General Public License for more details.

--    You should have received a copy of the GNU Affero General Public License
--    along with this program.  If not, see <http://www.gnu.org/licenses/>.
{-# LANGUAGE MultiParamTypeClasses, FunctionalDependencies #-}
module Lang.Value where
import Mapping
import Lang.Common
-- 模擬subtype
-- Shen的Type System更好，但Shen不支持中國字
data W物 = W首尾 W物 W物|W空|W字 Char|W數 Rational|W名 L列|
           W映 (Mapping W物 W物)|W境 (Mapping M名物 W物)|W機 (Mapping M名物 W物) X形 W物|W界機 JJ界機物|
           W陰|W陽|W引機 J機物|W譯機 J機物|W誤 W物|W構 M名物 L列 deriving (Eq, Ord, Show)
data Y映 = Y物映 (Mapping W物 W物)|Y境 (Mapping M名物 W物) -- deriving (Ord, Show) -- bug fixing

data L列 = L首尾 W物 L列|L空 deriving (Eq, Ord, Show)
data M名物 = M名 L列 deriving (Eq, Ord, Show)
data X形 = X首尾 M名物 X形|X空|X名 L列 deriving (Eq, Ord, Show)
data J機物 = J機 (Mapping M名物 W物) X形 W物|J界機 JJ界機物 deriving (Eq, Ord, Show)
data JJ界機物 = MkJJ界機物 (List String) Nat (List W物 -> W物) X形 W物
instance Eq JJ界機物 where
    MkJJ界機物 x _ _ _ _ == MkJJ界機物 y _ _ _ _ = x == y
instance Ord JJ界機物 where
    compare (MkJJ界機物 x _ _ _ _) (MkJJ界機物 y _ _ _ _) = compare x y
instance Show JJ界機物 where
    show (MkJJ界機物 x y _ z a) = "MkJJ界機物 " ++ showsPrec 11 x "" ++ " " ++ showsPrec 11 y "" ++ " _ " ++ showsPrec 11 z "" ++ " " ++ showsPrec 11 a ""

class C首尾 x y z | y -> x z, z -> x y where 首尾 :: x -> y -> z
class C空 x where 空 :: x
instance C首尾 W物 W物 W物 where 首尾 = W首尾
instance C空 W物 where 空 = W空
instance C首尾 W物 L列 L列 where 首尾 = L首尾
instance C空 L列 where 空 = L空
instance C首尾 M名物 X形 X形 where 首尾 = X首尾
instance C空 X形 where 空 = X空

class C名 x where 名 :: L列 -> x
instance C名 W物 where 名 = W名
instance C名 M名物 where 名 = M名
instance C名 X形 where 名 = X名

class C機 x where 機 :: Mapping M名物 W物 -> X形 -> W物 -> x
instance C機 W物 where 機 = W機
instance C機 J機物 where 機 = J機
class C界機 x where 界機 :: JJ界機物 -> x
instance C界機 W物 where 界機 = W界機
instance C界機 J機物 where 界機 = J界機
字 = W字
數 = W數
映 = W映
陰 = W陰
陽 = W陽
引機 = W引機
譯機 = W譯機
誤 = W誤
構 = W構
境 = W境
