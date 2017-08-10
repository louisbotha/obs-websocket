set obsdir=D:\projects\git\grove\joinin-obs\OBS-Studio-19.0.3-Full
set websocketdir=D:\projects\git\grove\joinin-obs\obs-websocket

d:
cd %websocketdir%\Release
copy obs*.* %obsdir%\obs-plugins\64bit /y
copy qt*.* %obsdir%\obs-plugins\64bit /y
pause
cd %obsdir%\bin\64bit\
obs64.exe
