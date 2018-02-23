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
module Lang.Read(readW) where
import Lang.Value
import Lang.Common
import Lang.Cast

readW :: String -> Maybe (W物, String)
readW xs = mapM 預 xs >>= 讀

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

讀 :: String -> Maybe (W物, String)
讀 (' ':xs) = 讀 xs
讀 (':':xs) = 讀 xs >>= \(_, rs) -> 讀 rs
讀 ('(':xs) = 讀列 xs
讀 ('|':xs) = 讀特名 xs >>= \(a, bs) -> Just (字列To名 a, bs)
讀 ('[':xs) = 讀用式 xs >>= \(x, xs) -> Just (首尾 用式名 x, xs)
讀 (';':xs) = 讀字 xs
讀 ('<':xs) = 讀名 xs >>= \(xs, rs) -> Just (case xs of
    [x] -> (x, rs)
    xs -> (W名 (建列 xs), rs))
讀 xs = 讀簡名 xs >>= \(a, bs, cs) -> case a of
    "" -> Nothing
    _ -> Just (建名 (a:bs), cs)

讀名 :: String -> Maybe (List W物, String)
讀名 ('>':xs) = Just ([], xs)
讀名 (' ':xs) = 讀名 xs
讀名 xs = 讀 xs >>= \(x, xs) -> 讀名 xs >>= \(ys, rs) -> Just (x:ys, rs)

讀簡名 (';':[]) = Nothing
讀簡名 (';':x:xs) = 讀簡名 xs >>= \(a, bs, cs) -> Just (x:a, bs, cs)
讀簡名 ('-':xs) = 讀簡名 xs >>= \(a, bs, cs) -> Just ("", a:bs, cs)
讀簡名 ('→':xs) = 讀簡名 xs >>= \(a, bs, cs) -> Just ("", "→":a:bs, cs)
讀簡名 ('?':[]) = Just ("?", [], "")
讀簡名 ('?':rs@(x:_)) = if is非名 x then Just ("?", [], rs) else Nothing
讀簡名 a@(x:xs) = if is非名 x then Just ("", [], a) else 讀簡名 xs >>= \(a, bs, cs) -> Just (x:a, bs, cs)
讀簡名 "" = Just ("", [], "")

讀特名 ('|':xs) = Just ("", xs)
讀特名 (';':[]) = Nothing
讀特名 (';':x:xs) = 讀特名 xs >>= \(a, bs) -> Just (x:a, bs)
讀特名 (x:xs) = 讀特名 xs >>= \(a, bs) -> Just (x:a, bs)
讀特名 "" = Nothing

讀列 (' ':'-':' ':xs) = 讀 xs >>= \(x, rs) -> 讀列 xs >>= \(y, rs) -> case y of
    W空 -> Just (x, rs)
    _ -> Nothing
讀列 (' ':xs) = 讀列 xs
讀列 (':':xs) = 讀 xs >>= \(_, rs) -> 讀列 rs
讀列 (')':xs) = Just (空, xs)
讀列 xs = 讀 xs >>= \(x, rs) -> 讀列 rs >>= \(xs, rs) -> Just (首尾 x xs, rs)

讀用式 :: String -> Maybe (W物, String)
讀用式 (' ':xs) = 讀用式 xs
讀用式 (':':xs) = 讀 xs >>= \(_, rs) -> 讀用式 rs
讀用式 (']':xs) = Just (空, xs)
讀用式 xs = 讀 xs >>= \(x, rs) -> 讀用式 rs >>= \(xs, rs) -> Just (首尾 x xs, rs)

讀字 (';':xs) = case xs of
    ';':rs -> Just (字 ';', rs)
    '空':rs -> Just (字 ' ', rs)
    _ -> Nothing
讀字 (x:xs) = Just (字 x, xs)
讀字 _ = Nothing

