rmdir /s /q benchmarks

for /l %%i in (1, 1, 30) do (
  run.bat point_dist.exe C
  run.bat "py point_dist.py" Python
  run.bat "matlab -nodesktop -noawt -batch point_dist;exit;" Matlab
  rmdir /s /q benchmarks
)


for /l %%i in (1, 1, 30) do (
	run.bat point_dist.exe C
	run.bat "py point_dist.py" Python
	run.bat "matlab -nodesktop -noawt -batch point_dist;exit;" Matlab
)
