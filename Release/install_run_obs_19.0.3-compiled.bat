set obsdir=D:\projects\git\grove\joinin-obs\obs-studio-19.0.3\rundir\Release
set websocketdir=D:\projects\git\grove\joinin-obs\obs-websocket

d:
cd %websocketdir%\Release
copy obs-websocket.dll %obsdir%\obs-plugins\64bit /y
copy qt*.* %obsdir%\obs-plugins\64bit /y
pause
cd %obsdir%\bin\64bit\
obs64.exe
