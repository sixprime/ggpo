@echo off

REM Test the vectorwar sample by starting 2 clients connected
REM back to each other.
REM
REM Controls: Arrows to move
REM           Press 'D' to fire
REM           Press 'P' to show performance monitor
REM           Shift to strafe

pushd ..\build\bin\x64\Release
del *.log

start VectorWar.exe 127.0.0.1:56789 4 1
start VectorWar.exe 127.0.0.1:56789 4 2
start VectorWar.exe 127.0.0.1:56789 4 3
start VectorWar.exe 127.0.0.1:56789 4 4

popd
