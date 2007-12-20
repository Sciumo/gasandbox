mkdir ..\ga_sandbox_win32_binary_executables
copy c:\windows\glut32.dll ..\ga_sandbox_win32_binary_executables
copy .\vs2005\release\*.exe ..\ga_sandbox_win32_binary_executables
copy .\chap3\ex4\image2.raw ..\ga_sandbox_win32_binary_executables
copy .\chap3\ex4\image3.raw ..\ga_sandbox_win32_binary_executables
copy .\chap10\ex3\calibration_data.txt ..\ga_sandbox_win32_binary_executables
copy .\chap12\ex3\silly_moves.txt ..\ga_sandbox_win32_binary_executables

copy .\solutions\vs2005\release\*.exe ..\ga_sandbox_win32_binary_executables

cd ..
del ga_sandbox_win32_binary_executables.tar
del ga_sandbox_win32_binary_executables.tar.gz
tar cf ga_sandbox_win32_binary_executables.tar ga_sandbox_win32_binary_executables
gzip -9 ga_sandbox_win32_binary_executables.tar
cd ga_sandbox_win32_binary_executables
del /Q *.*
cd ..
rmdir /S /Q ga_sandbox_win32_binary_executables
cd ga_sandbox