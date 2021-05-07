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

REM <session_endpoint> <session_num_players> <session_player_position[1..session_num_players]>
start VectorWar.exe 127.0.0.1:56789 2 1
start VectorWar.exe 127.0.0.1:56789 2 2

popd
