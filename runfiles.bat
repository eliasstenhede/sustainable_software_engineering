for /l %%i in (1, 1, 20) do (
	run.bat point_dist.exe C
	run.bat "py point_dist.py" Python
	run.bat "matlab -nodesktop -noawt -batch point_dist;exit;" Matlab
)
