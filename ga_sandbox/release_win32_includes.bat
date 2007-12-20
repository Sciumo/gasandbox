rem called from release_win32_libraries.bat and release_win64_libraries.bat
mkdir ..\tmp\ga_sandbox\ext_include
mkdir ..\tmp\ga_sandbox\ext_include\GL
mkdir ..\tmp\ga_sandbox\ext_include\opencv
mkdir ..\tmp\ga_sandbox\ext_include\antlr
mkdir ..\tmp\ga_sandbox\ext_include\FL

copy c:\include\opencv\*.* ..\tmp\ga_sandbox\ext_include\opencv
copy c:\include\antlr\*.* ..\tmp\ga_sandbox\ext_include\antlr
copy c:\include\FL\*.* ..\tmp\ga_sandbox\ext_include\FL
copy c:\include\GL\glut.h ..\tmp\ga_sandbox\ext_include\GL
