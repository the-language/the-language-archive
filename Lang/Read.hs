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

讀 :: String -> Maybe (W物, String)
讀 xs = mapM 預 xs >>= p讀

has [] _ = False
has (y:ys) x = if x==y then True else has ys x

is非名 :: Char -> Bool
is非名 x = has " \t\r\n()[]:|‘’,“”→<>-?" x

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

p讀 :: String -> Maybe (W物, String)
p讀 (' ':xs) = p讀 xs
p讀 (':':xs) = p讀 xs >>= \(_, rs) -> p讀 rs
p讀 ('(':xs) = p讀列 xs
p讀 ('|':xs) = p讀特名 xs >>= \(a, bs) -> Just (字列To名 a, bs)
p讀 ('[':xs) = p讀用式 xs >>= \(x, xs) -> Just (首尾 用式名 x, xs)
p讀 (';':xs) = p讀字 xs
p讀 ('<':xs) = p讀名 xs >>= \(xs, rs) -> Just (case xs of
    [x] -> (x, rs)
    xs -> (W名 (建列 xs), rs))
p讀 xs = p讀簡名 xs >>= \(a, bs, cs) -> case a of
    "" -> Nothing
    _ -> Just (建名 (a:bs), cs)

p讀名 :: String -> Maybe (List W物, String)
p讀名 ('>':xs) = Just ([], xs)
p讀名 (' ':xs) = p讀名 xs
p讀名 xs = p讀 xs >>= \(x, xs) -> p讀名 xs >>= \(ys, rs) -> Just (x:ys, rs)

p讀簡名 (';':[]) = Nothing
p讀簡名 (';':x:xs) = p讀簡名 xs >>= \(a, bs, cs) -> Just (x:a, bs, cs)
p讀簡名 ('-':xs) = p讀簡名 xs >>= \(a, bs, cs) -> Just ("", a:bs, cs)
p讀簡名 ('→':xs) = p讀簡名 xs >>= \(a, bs, cs) -> Just ("", "→":a:bs, cs)
p讀簡名 ('?':[]) = Just ("?", [], "")
p讀簡名 ('?':rs@(x:_)) = if is非名 x then Just ("?", [], rs) else Nothing
p讀簡名 a@(x:xs) = if is非名 x then Just ("", [], a) else p讀簡名 xs >>= \(a, bs, cs) -> Just (x:a, bs, cs)
p讀簡名 "" = Just ("", [], "")

p讀特名 ('|':xs) = Just ("", xs)
p讀特名 (';':[]) = Nothing
p讀特名 (';':x:xs) = p讀特名 xs >>= \(a, bs) -> Just (x:a, bs)
p讀特名 (x:xs) = p讀特名 xs >>= \(a, bs) -> Just (x:a, bs)
p讀特名 "" = Nothing

p讀列 (' ':'-':' ':xs) = p讀 xs >>= \(x, rs) -> p讀列 xs >>= \(y, rs) -> case y of
    W空 -> Just (x, rs)
    _ -> Nothing
p讀列 (' ':xs) = p讀列 xs
p讀列 (':':xs) = p讀 xs >>= \(_, rs) -> p讀列 rs
p讀列 (')':xs) = Just (空, xs)
p讀列 xs = p讀 xs >>= \(x, rs) -> p讀列 rs >>= \(xs, rs) -> Just (首尾 x xs, rs)

p讀用式 :: String -> Maybe (W物, String)
p讀用式 (' ':xs) = p讀用式 xs
p讀用式 (':':xs) = p讀 xs >>= \(_, rs) -> p讀用式 rs
p讀用式 (']':xs) = Just (空, xs)
p讀用式 xs = p讀 xs >>= \(x, rs) -> p讀用式 rs >>= \(xs, rs) -> Just (首尾 x xs, rs)

p讀字 (';':xs) = case xs of
    ';':rs -> Just (字 ';', rs)
    '空':rs -> Just (字 ' ', rs)
    _ -> Nothing
p讀字 (x:xs) = Just (字 x, xs)
p讀字 _ = Nothing

