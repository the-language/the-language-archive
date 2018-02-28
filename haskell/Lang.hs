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
module Lang(main) where
import Lang.Lang
import Lang.Read
import Lang.Value
import Lang.Cast
import Lang.Show
import Mapping

type St = (Mapping M名物 W物, W物)
initst :: St
initst = (空境, 空)

parseError :: IO ()
parseError = putStrLn "錯誤： 讀取錯誤"

loop :: St -> IO St
loop _s@(e, it) = do
    putStr "語> "
    l <- getLine
    case l of
        '!' : cmd -> runCmd cmd _s
        _ -> case 讀 l of
            Just (x, "") -> do
                let it = 算 x e
                case it of
                    W誤 _ -> do
                        putStrLn "ERROR"
                        return (e, it)
                    _ -> do
                        putStrLn (示 it)
                        return (e, it)
            _ -> do
                parseError
                return _s

runCmd :: String -> St -> IO St
runCmd ('名':' ':名)  _s@(e, it) =
    let
      m' = do
        (x, "") <- 讀 名
        物To名 x
    in case m' of
        Just 名 -> return (mappingSet e 名 it, it)
        Nothing -> do
            parseError
            return _s

main :: IO ()
main = f initst
  where
    f :: St -> IO ()
    f s = do
        s <- loop s
        f s

