rem called from release_win32_libraries.bat and release_win64_libraries.bat
mkdir ..\tmp\ga_sandbox\ext_include
mkdir ..\tmp\ga_sandbox\ext_include\GL

copy c:\include\opencv ..\tmp\ga_sandbox\ext_include
copy c:\include\antlr ..\tmp\ga_sandbox\ext_include
copy c:\include\FL ..\tmp\ga_sandbox\ext_include
copy c:\include\GL\glut.h ..\tmp\ga_sandbox\GL
