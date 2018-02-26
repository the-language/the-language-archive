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
module Package(取) where
import Lang.Value
import Lang.Read(讀)
import Lang.Common
import Network.Http.Client(get, concatHandler)
import Data.Text.Encoding(encodeUtf8, decodeUtf8)
import Data.Text(pack, unpack)
import Control.Monad(join)
import System.IO.Unsafe(unsafePerformIO)
import Control.Exception(catch, SomeException(SomeException))
import Control.Applicative.Alternative((<|>))

cat :: IO a -> IO (Maybe a)
cat x = catch (pure <$> x) (\(SomeException _) -> return Nothing)

httpGet :: String -> IO (Maybe String)
httpGet url = cat $ unpack . decodeUtf8 <$> get (encodeUtf8 (pack url)) concatHandler

githubGet :: String -> String -> String -> List String -> IO (Maybe String)
githubGet u r b f = httpGet $ "https://raw.githubusercontent.com/" ++ u ++"/"++ r ++"/"++ b ++"/"++ join f

langGet :: String -> List String -> IO (Maybe String)
langGet r f = githubGet "the-language" r "master" f

cast :: M名物 -> Maybe (List String)
cast (M名 x) = f1 x
  where
    f1 :: L列 -> Maybe (List String)
    f1 L空 = pure []
    f1 (L首尾 首 尾) = (:) <$> f2 首 <*> f1 尾
      where
        f2 :: W物 -> Maybe String
        f2 (W首尾 (W字 a) d) = (:) a <$> f2 d
        f2 W空 = pure []
        f2 _ = Nothing

讀完 :: String -> W物
讀完 x = case 讀 x of Just (x, "") -> x

取 :: M名物 -> W物
取 m = 讀完 $ case cast m of
    Just [x] -> unsafePerformIO $ do
        (Just r) <- (<|>) <$> langGet x ["述"] <*> langGet "libs" [x]
        return r

