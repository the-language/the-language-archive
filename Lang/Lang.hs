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
module Lang.Lang where
import Lang.Value
import Lang.Cast
import Lang.Common
import Mapping

wip = error "WIP"

infixr 0 ?
W誤 _ ? _ = Nothing
_ ? x = x

界誤 :: List String -> List W物 -> W物
界誤 n xs = 誤 (構 界誤名 (首尾 (建名 n) (建列 xs)))

mkfM :: List String -> (List W物 -> Maybe W物) -> (List W物 -> W物)
mkfM n f = \xs -> case f xs of
    Just x -> x
    Nothing -> 界誤 n xs

class C建參 x where 建參 :: Nat -> x
instance C建參 X形 where 建參 x = 建列 (map (\x -> 建名[show x]) [x,x-1..1])
instance C建參 W物 where 建參 x = 建列 (map (\x -> 建名[show x]) [x,x-1..1])

建界名 :: List String -> W物
建界名 n = (首尾 用界名 (首尾 (建名 n) 空))

f :: List String -> Nat -> (List W物 -> W物) -> (M名物, W物)
f n c x = (建名 n, 界機 (MkJJ界機物 n c x (建參 c) (首尾 (建界名 n) (建參 c))))

fM :: List String -> Nat -> (List W物 -> Maybe W物) -> (M名物, W物)
fM n c x = f n c (mkfM n x)

m :: List String -> Nat -> (Mapping M名物 W物 -> List W物 -> Maybe W物) -> (M名物, W物)
m n c x = (建名 n, 引機 (界機 (MkJJ界機物 n ce f (建參 ce) (建列[建界名["算"], 未算, 建名[show ce]]))))
  where
    f :: (List W物 -> W物)
    f _a@(e : xs) = case (物To境 e >>= \e -> x e xs) of
        Just x -> x
        Nothing -> 界誤 n _a
    
    ce :: Nat
    ce = c+1
    
    未算 :: W物
    未算 = 建首尾 (引 用式名) (建首尾 (引 (建界名 n)) (連參 c))
    
    連參 :: Nat -> W物
    連參 1 = 建首尾 (建名["1"]) (建界名["空"])
    連參 n = 建首尾 (建名[show n]) (連參 (n-1))
    
    建首尾 :: W物 -> W物 -> W物
    建首尾 a d = 建列[建界名["首尾"], a, d]
    
    引 :: W物 -> W物
    引 x = 建式 (建界名["引"]) [x]
    
    建式 :: W物 -> List W物 -> W物
    建式 x ys = 建列 (用式名 : x : ys)

空境 :: Mapping M名物 W物
空境 = (listToMapping [
    (fM["等","?"]2(\[x,y] -> x?y? Just (建陰陽 (x == y)))),
    (fM["首尾","?"]1(\[x] -> x? case x of
        W首尾 _ _ -> Just 陽
        _ -> Just 陰)),
    (f["首尾"]2(\[x,y] -> 首尾 x y)),
    (fM["首尾","首"]1(\[x] -> x? case x of
        W首尾 x _ -> Just x
        _ -> Nothing)),
    (fM["首尾","尾"]1(\[x] -> x? case x of
        W首尾 _ x -> Just x
        _ -> Nothing)),
    (fM["空","?"]1(\[x] -> x? case x of
        W空 -> Just 陽
        _ -> Just 陰)),
    (建名["列"], 機 MappingNil (建名 ["1"]) (建名 ["1"])),
    (fM["字","?"]1(\[x] -> x? case x of
        W字 _ -> Just 陽
        _ -> Just 陰)),
    (fM["名","?"]1(\[x] -> x? case x of
        W名 _ -> Just 陽
        _ -> Just 陰)),
    (fM["列","→","名"]1(\[x] -> x? 名 <$> 物To列 x)),
    (fM["名","→","列"]1(\[x] -> x? case x of
        W名 x -> Just (列To物 x)
        _ -> Nothing)),
    (fM["映","?"]1(\[x] -> x? case x of
        W映 _ -> Just 陽
        _ -> Just 陰)),
    (建名["映","空"], 映 MappingNil),
    (fM["映","改"]3(\[h, k, v] -> h? case h of
        W映 h -> Just (W映 (mappingSet h k v))
        _ -> Nothing)),
    (fM["映","取"]3(\[h, k, d] -> h? case h of
        W映 h -> Just (mappingRef h k d)
        _ -> Nothing)),
    (fM["映","含","?"]2(\[h, k] -> h? case h of
        W映 h -> Just (建陰陽 (mappingHas h k))
        _ -> Nothing)),
    (f["映","删"]2(\[hw, k] -> case hw of
        W映 h -> case mappingRemove h k of
            Just x -> W映 x
            Nothing -> 誤 (構 (名 (建列 [字列To名 "!", 字列To名 "界", 建名 ["映","删"]])) (首尾 (建名 ["無"]) (首尾 hw (首尾 k 空))))
        _ -> 誤 (構 (名 (建列 [字列To名 "!", 字列To名 "界", 建名 ["映","删"]])) (首尾 (建名 ["非"]) (首尾 hw (首尾 k 空)))))),
    (fM["映","→","列"]1(\[h] -> h? case h of
        W映 h -> Just (建列 (map (\(a, d) -> 首尾 a d) (mappingToList h)))
        _ -> Nothing)),
    (fM["機","?"]1(\[x] -> x? case x of
        W機 _ _ _ -> Just 陽
        W界機 _ -> Just 陽
        _ -> Just 陰)),
    (fM["機"]2(\[x, y] -> x? fmap (\x -> 機 MappingNil x y) (物To形 x))),
    (建名["用"], wip),
    (fM["機","形"]1(\[x] -> x? case x of
        W機 _ x _ -> Just (形To物 x)
        W界機 (MkJJ界機物 _ _ _ x _) -> Just (形To物 x)
        _ -> Nothing)),
    (fM["機","物"]1(\[x] -> x? wip)),
    (m["入"]2(\e [x, w] -> 物To形 x >>= \x -> Just (機 e x w))),
    (建名["陰"], 陰),
    (建名["陽"], 陽),
    (fM["若"]3(\[b, x, y] -> b? case b of
        W陽 -> Just x
        _ -> Just y)),
    (fM["引機","?"]1(\[x] -> x? case x of
        W引機 _ -> Just 陽
        _ -> Just 陰)),
    (fM["引機"]1(\[x] -> x? W引機 <$> 物To機物 x)),
    (fM["引機","反"]1(\[x] -> x? case x of
        W引機 x -> Just (機物To物 x)
        _ -> Nothing)),
    (fM["譯機","?"]1(\[x] -> x? case x of
        W譯機 _ -> Just 陽
        _ -> Just 陰)),
    (fM["譯機"]1(\[x] -> x? W譯機 <$> 物To機物 x)),
    (fM["譯機","反"]1(\[x] -> x? case x of
        W譯機 x -> Just (機物To物 x)
        _ -> Nothing)),
    (建名["引"], wip),
    (f["誤","？"]1(\[x] -> case x of
        W誤 _ -> 陽
        _ -> 陰)),
    (f["誤"]1(\[x] -> W誤 x)),
    (fM["誤","反"]1(\[x] -> case x of
        W誤 x -> Just x
        _ -> Nothing)),
    (fM["算"]2(\[x,e] -> x?e? 算 x <$> 物To境 e)),
    (建名["境","名今"], wip),
    (建名["境","改"], wip),
    (建名["境","空"], W映 (境ToMapping 空境)),
    (建名["命名"], wip),
    (fM["構","?"]1(\[x] -> x? case x of
        W構 _ _ -> Just 陽
        _ -> Just 陰)),
    (fM["構"]2(\[n,xs] -> 物To列 xs >>= \xs -> case n of
        W名 x -> Just (構 (名 x) xs)
        _ -> Nothing)),
    (fM["構","名"]1(\[x] -> x? case x of
        W構 (M名 x) _ -> Just (名 x)
        _ -> Nothing)),
    (fM["構","列"]1(\[x] -> x? case x of
        W構 _ xs -> Just (列To物 xs)
        _ -> Nothing)),
    (fM["取","未算"]1(\[x] -> x? case x of
        W名 x -> wip
        _ -> Nothing)),
    (建名["取"], wip),
    (fM["界","含","?"]1(\[x] -> x? case x of
        W名 x -> case x of
            _ -> Just 陰
        _ -> Nothing)),
    (fM["界","取"]1(\[x,y] -> x? case x of
        W名 x -> case x of
            _ -> Just y
        _ -> Nothing))
    ])

算 :: W物 -> Mapping M名物 W物 -> W物
算 x@(W名 m) e = mappingRef e (名 m) (界誤 ["算"] [x,境To物 e])
算 (W首尾 y x) e | y == 用式名 = case x of
    W首尾 f xs -> wip
    _ -> 界誤 ["算"] [x,境To物 e]
算 (W首尾 y x) e | y == 用界名 = wip
算 _x@(W首尾 f as) e = case 物ToList as of
    Just xs -> case 物To機物 f of
        Just f -> 用 f (map (\x->算 x e) xs)
        Nothing -> 界誤 ["用"] [f,as]
    Nothing -> 界誤 ["算"] [_x,境To物 e]
算 x@(W誤 _) e = 界誤 ["算"] [x,境To物 e]
算 x e = x

match :: Mapping M名物 W物 -> X形 -> List W物 -> Maybe (Mapping M名物 W物)
match m (X名 x) v = Just (mappingSet m (名 x) (建列 v))
match m X空 [] = Just m
match m (X首尾 (M名 x) xs) (v:vs) = match (mappingSet m (名 x) v) xs vs
match _ _ _ = Nothing

用 :: J機物 -> List W物 -> W物
用 (J機 e a x) ws = case match e a ws of
    Just e -> 算 x e
    Nothing -> 界誤 ["用"] [(機 e a x),建列 ws]
用 (J界機 a_@(MkJJ界機物 _ c f _ _)) ws = if length ws == c then f ws else 界誤 ["用"] [界機 a_,建列 ws]

