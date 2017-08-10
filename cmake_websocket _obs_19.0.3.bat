rem git clone --recursive https://github.com/louisbotha/obs-websocket.git
rem -G "Visual Studio 14 2015 Win64" 
rem -G "Visual Studio 12 2013 Win64" 

rem manually add this path to C++ additional include directories of the obs-websocket project: D:\projects\git\grove\joinin-obs\obs-studio-19.0.3\libobs\util (for missing config.h)
rem set build to release and run exe from D:\projects\git\grove\joinin-obs\obs-websocket-4.1.0\Release
rem output in D:\projects\git\grove\joinin-obs\obs-websocket\Release\

set cmakedir="C:\Program Files\CMake\bin"
set obsdir=D:\projects\git\grove\joinin-obs\obs-studio-19.0.3
set websocketdir=D:\projects\git\grove\joinin-obs\obs-websocket

del CMakeCache.txt
del obs-websocket.sln

%cmakedir%\cmake -G "Visual Studio 12 2013 Win64" -D QTDIR=C:\Qt5\5.7.0\msvc2015_64 -D LIBOBS_INCLUDE_DIR=%obsdir%\libobs -D LIBOBS_LIB=%obsdir%\build\Release\obs.lib -D OBS_FRONTEND_LIB=%obsdir%\build\Release\obs-frontend-api.lib %websocketdir%\

pause