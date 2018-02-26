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
module Lang.Read(讀) where
import Lang.Value
import Lang.Common
import Lang.Cast
import Mapping

讀 :: String -> Maybe (W物, String)
讀 xs = r MappingNil xs

預 '\t'=Just ' '
預 '\r'=Just ' '
預 '\n'=Just ' '
預 '（'=Just '('
預 '）'=Just ')'
預 '：'=Just ':'
預 '；'=Just ';'
預 '\''=Nothing
預 '`'=Nothing
預 '"'=Nothing
預 '！'=Just '!'
預 '？'=Just '?'
預 x=Just x

infixl 1 >?=
x >?= f = fmap f x

type RMap = Mapping String W物
type Reader x = RMap -> String -> Maybe (x, String)

r完 :: RMap -> String -> W物
r完 m xs = case r m xs of Just (x, "") -> x

-- 計劃建立一個新的Monad

r :: Reader W物
r m ('名':'(':xs) = r物列 m xs >?= \(xs, rs) -> (名 (建列 xs), rs)
r m ('(':xs) = r首尾 m xs
r m ('字':x:xs) = pure (字 x, xs)
r m ('定':'(':xs) = r定 m xs
r m ('定':xs) = r至空 m xs >>= \x -> if mappingHas m x then pure (mappingRef m x (error "")) else Nothing
r m ('空':xs) = pure (空, xs)
r m ('陰':xs) = pure (陰, xs)
r m ('陽':xs) = pure (陽, xs)
r m ('映':xs) = r映 m xs
r m ('機':rs) = r機 (\x b -> 機 MappingNil x b) m rs
r m ('引':'機':rs) = r機 (\x b -> 引機 (機 MappingNil x b)) m rs
r m ('譯':'機':rs) = r機 (\x b -> 譯機 (機 MappingNil x b)) m rs
r m ('誤':'(':rs) = do
    (x, ')':rs) <- r m rs
    return (誤 x)
r m ('構':'(':'(':rs) = do
    (ns, rs) <- r物列 m rs
    let n = 名 (建列 ns)
    (_, '(':rs) <- r空 m rs
    (x, ')':rs) <- r物列 m rs
    return (構 ns (建列 x))
r m (' ':rs) = r m rs
r _ _ = Nothing

r列式 :: Nat -> Reader String
r列式 n m (')':rs) = if x==0 then pure ("", rs) else r列式 (n-1) m rs >?= \(xs, rs) -> (x:xs, rs)
r列式 n m (x:rs) = r列式 n m rs >?= \(xs, rs) -> (x:xs, rs)
r列式 n m ('(':rs) = r列式 (n+1) m rs >?= \(xs, rs) -> (x:xs, rs)
r列式 _ _ = Nothing

r式 :: Reader String
r式 m ('名':'(':xs) = error "WIP"

r機 :: (X形 -> W物 -> a) -> Reader a
r機 r m rs = do
    '(':rs <- return rs
    (x, rs) <- r m rs
    x <- 物To形 x
    (b, ')':rs) <- r m rs
    return (r x b)

r定甲 :: Reader (List (String, String))
r定甲 m ('(':rs) = do
    (名, rs) <- r至空 m rs
    (值, ')':rs) <- r式 m rs
    (_, rs) <- r空 m rs
    (xs, rs) <- r定甲 m rs
    return ((名, 值):xs, rs)
r定甲 m xs = pure ([], xs)

r定 :: Reader W物
r定 m ('(':rs) = do
    (xs, ')':rs) <- r定甲 m rs
    let m' = (let {m' = mappingAppendList m xs'; xs' = map (\(k, v) -> (k, r完 m' v)) xs} in m')
    (x, ')':rs) <- r m' rs
    return (x, rs)

r至空 :: Reader String
r至空 m r@(' ':_) = pure ("", r)
r至空 m (x:xs) = r至空 m xs >?= \(xs, rs) -> (x:xs, rs)
r至空 m "" = pure ("", "")

r空 :: Reader String
r空 m xs = pure $ rs "" xs
  where
    rs :: String -> String -> (String, String)
    rs x "" = ("", x)
    rs a (' ':xs) = rs (' ':a) xs

r物列 :: Reader (List W物)
r物列 = error "WIP"

r首尾 :: Reader W物
r首尾 = error "WIP"
