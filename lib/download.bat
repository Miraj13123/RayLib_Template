

rem dont run this bat by clicking
rem run this from root folder of this repo





curl -L -o lib\raylib-5.5_win64_mingw-w64.zip https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_win64_mingw-w64.zip
rem gh release download 5.5 --repo raysan5/raylib --pattern "raylib-5.5_win64_mingw-w64.zip" --dir lib
tar -xf lib\raylib-5.5_win64_mingw-w64.zip -C lib
DEL "lib\raylib-5.5_win64_mingw-w64.zip"

curl -L -o lib\raygui-4.0.zip https://github.com/raysan5/raygui/archive/refs/tags/4.0.zip
tar -xf lib\raygui-4.0.zip -C lib
del lib\raygui-4.0.zip