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
module Lang.Cast where
import Lang.Value
import Lang.Common
import Mapping

--GHC 不能用像Idris的'Cast'的Type Class

class C建字列 x where 建字列 :: String -> x
instance C建字列 W物 where
    建字列 [] = 空
    建字列 (x:xs) = 首尾 (字 x) (建字列 xs)
instance C建字列 L列 where
    建字列 [] = 空
    建字列 (x:xs) = 首尾 (字 x) (建字列 xs)

class C字列To名 x where 字列To名 :: String -> x
instance C字列To名 W物 where 字列To名 xs = 名 (建字列 xs)
instance C字列To名 M名物 where 字列To名 xs = 名 (建字列 xs)
instance C字列To名 X形 where 字列To名 xs = 名 (建字列 xs)

class C建名 x where 建名 :: List String -> x
instance C建名 W物 where
    建名 [x] = 字列To名 x
    建名 xs = 名 (建列 (map 字列To名 xs))
instance C建名 M名物 where
    建名 [x] = 字列To名 x
    建名 xs = 名 (建列 (map 字列To名 xs))
instance C建名 X形 where
    建名 [x] = 字列To名 x
    建名 xs = 名 (建列 (map 字列To名 xs))

class C用式名 x where 用式名 :: x
instance C用式名 W物 where 用式名 = 建名 ["!", "式"]
instance C用式名 M名物 where 用式名 = 建名 ["!", "式"]

建式 :: W物 -> List W物 -> W物
建式 x ys = 建列 (用式名 : x : ys)

建界名 :: List String -> W物
建界名 n = (首尾 用界名 (首尾 (建名 n) 空))

class C用界名 x where 用界名 :: x
instance C用界名 W物 where 用界名 = 建名 ["!", "界"]
instance C用界名 M名物 where 用界名 = 建名 ["!", "界"]

class C界誤名 x where 界誤名 :: x
instance C界誤名 W物 where 界誤名 = 建名 ["!", "界"]
instance C界誤名 M名物 where 界誤名 = 建名 ["!", "界"]

class C建列 x y | y -> x where 建列 :: List x -> y
instance C建列 W物 W物 where
    建列 [] = 空
    建列 (x:xs) = 首尾 x (建列 xs)
instance C建列 M名物 X形 where
    建列 [] = 空
    建列 (x:xs) = 首尾 x (建列 xs)
instance C建列 W物 L列 where
    建列 [] = 空
    建列 (x:xs) = 首尾 x (建列 xs)

建陰陽 True = 陽
建陰陽 False = 陰

物To列 :: W物 -> Maybe L列
物To列 W空 = Just 空
物To列 (W首尾 首 尾) = fmap (\尾 -> (首尾 首 尾)) (物To列 尾)
物To列 _ = Nothing

物ToList :: W物 -> Maybe (List W物)
物ToList W空 = Just []
物ToList (W首尾 首 尾) = 物ToList 尾 >>= \尾 -> Just (首 : 尾)
物ToList _ = Nothing

列To物 :: L列 -> W物
列To物 L空 = 空
列To物 (L首尾 首 尾) = 首尾 首 (列To物 尾)

物To形 :: W物 -> Maybe X形
物To形 (W名 x) = Just (名 x)
物To形 W空 = Just 空
物To形 (W首尾 (W名 首) 尾) = fmap (\尾 -> 首尾 (名 首) 尾) (物To形 尾)
物To形 _ = Nothing

形To物 :: X形 -> W物
形To物 (X名 x) = 名 x
形To物 X空 = 空
形To物 (X首尾 (M名 首) 尾) = 首尾 (名 首) (形To物 尾)

物To機物 :: W物 -> Maybe J機物
物To機物 (W機 x y z) = Just (機 x y z)
物To機物 (W界機 x) = Just (界機 x)
物To機物 _ = Nothing

境ToMapping :: Mapping M名物 W物 -> Mapping W物 W物
境ToMapping x = listToMapping (map (\(M名 k, v) -> (名 k, v)) (mappingToList x))

境To物 :: Mapping M名物 W物 -> W物
境To物 = 境

mappingTo境 :: Mapping W物 W物 -> Maybe (Mapping M名物 W物)
mappingTo境 x = listToMapping <$> mapM (\x -> case x of{(W名 k, v) -> Just (名 k, v);_ -> Nothing}) (mappingToList x)
物To境 :: W物 -> Maybe (Mapping M名物 W物)
物To境 (W映 x) = mappingTo境 x
物To境 (W境 x) = Just x
物To境 _ = Nothing

機物To物 :: J機物 -> W物
機物To物 (J機 x y z) = 機 x y z
機物To物 (J界機 x) = 界機 x

