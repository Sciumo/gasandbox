mkdir ..\ga_sandbox_win32_binary
copy .\vs2005\release\*.exe ..\ga_sandbox_win32_binary
copy .\chap3\ex4\image2.raw ..\ga_sandbox_win32_binary
copy .\chap3\ex4\image3.raw ..\ga_sandbox_win32_binary
copy .\chap10\ex3\calibration_data.txt ..\ga_sandbox_win32_binary
copy .\chap12\ex3\silly_moves.txt ..\ga_sandbox_win32_binary

copy .\solutions\vs2005\release\*.exe ..\ga_sandbox_win32_binary

cd ..
del ga_sandbox_win32_binary.tar
del ga_sandbox_win32_binary.tar.gz
tar cf ga_sandbox_win32_binary.tar ga_sandbox_win32_binary
gzip -9 ga_sandbox_win32_binary.tar
cd ga_sandbox_win32_binary
del /Q *.*
cd ..
del /Q ga_sandbox_win32_binary
cd ga_sandbox