rem This file copies the requires win32 libraries and packs them (works only when libraries are in c:\lib32 and include files in c:\include
mkdir ..\tmp
mkdir ..\tmp\ga_sandbox
mkdir ..\tmp\ga_sandbox\lib_win32
mkdir ..\tmp\ga_sandbox\vs2005

copy lib_win32_readme.txt ..\tmp\lib_win32_readme.txt

copy c:\windows\glut32.dll ..\tmp\ga_sandbox\vs2005\glut32.dll

copy c:\lib32\antlrmt.lib ..\tmp\ga_sandbox\lib_win32\antlr.lib
copy c:\lib32\antlrdmt.lib ..\tmp\ga_sandbox\lib_win32\antlrd.lib
copy c:\lib32\glut32.lib ..\tmp\ga_sandbox\lib_win32\glut32.lib
copy c:\lib32\cxcoremt.lib ..\tmp\ga_sandbox\lib_win32\cxcore.lib
copy c:\lib32\cxcoredmt.lib ..\tmp\ga_sandbox\lib_win32\cxcored.lib

copy c:\lib32\fltkmt.lib ..\tmp\ga_sandbox\lib_win32\fltk.lib
copy c:\lib32\fltkdmt.lib ..\tmp\ga_sandbox\lib_win32\fltkd.lib
copy c:\lib32\fltkglmt.lib ..\tmp\ga_sandbox\lib_win32\fltkgl.lib
copy c:\lib32\fltkgldmt.lib ..\tmp\ga_sandbox\lib_win32\fltkgld.lib

call release_win32_includes.bat

cd ..\tmp
del ga_sandbox_win32_binary_libraries.tar
del ga_sandbox_win32_binary_libraries.tar.gz
tar cf ga_sandbox_win32_binary_libraries.tar ga_sandbox lib_win32_readme.txt
gzip -9 ga_sandbox_win32_binary_libraries.tar
move ga_sandbox_win32_binary_libraries.tar.gz ..
cd ..
rmdir /Q /S tmp
cd ga_sandbox