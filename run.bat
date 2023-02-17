@echo off

set EXECUTABLE_FILE=%1
set SAVE_FOLDER=%2

if not exist benchmarks mkdir benchmarks
if not exist "benchmarks\%SAVE_FOLDER%" mkdir "benchmarks\%SAVE_FOLDER%"

set dtStamp24=%time:~3,2%%time:~6,2%
set "OUT_FILE=benchmarks\%SAVE_FOLDER%\benchmark_%dtStamp24%.csv"
"C:\Program Files\Intel\Power Gadget 3.6\PowerLog3.0.exe" -file %OUT_FILE% -cmd %EXECUTABLE_FILE%
