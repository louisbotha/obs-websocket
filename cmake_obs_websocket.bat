rem git clone --recursive https://github.com/louisbotha/obs-websocket.git
rem -G "Visual Studio 14 2015 Win64" 
rem -G "Visual Studio 12 2013 Win64" 
cmake -G "Visual Studio 12 2013 Win64" -D QTDIR=D:\Qt5\5.7.0\msvc2013_64 -D LIBOBS_INCLUDE_DIR=D:\projects\git\grove\obs-studio\libobs -D LIBOBS_LIB=D:\projects\git\grove\obs-studio\build\Release\obs.lib -D OBS_FRONTEND_LIB=D:\projects\git\grove\obs-studio\build\Release\obs-frontend-api.lib D:\projects\git\grove\obs-websocket
pause