@echo off

REM Test the vectorwar sample by starting 2 clients connected
REM back to each other.
REM
REM Controls: Arrows to move
REM           Press 'D' to fire
REM           Press 'P' to show performance monitor
REM           Shift to strafe

REM pushd ..\build\bin\x64\Release
pushd ..\build\bin\x64\Debug

del *.log

REM <session_endpoint> <session_num_players> <session_player_position[1..session_num_players]>
REM start VectorWar.exe 127.0.0.1:56789 3 1
REM start VectorWar.exe 127.0.0.1:56789 3 2
start VectorWar.exe 127.0.0.1:56789 3 3

popd
