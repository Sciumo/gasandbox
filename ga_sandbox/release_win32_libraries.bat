rem This file copies the requires win32 libraries and packs them (works only when libraries are in c:\lib32 and include files in c:\include
mkdir ..\tmp
mkdir ..\tmp\ga_sandbox
mkdir ..\tmp\ga_sandbox\lib_win32

copy c:\lib32\antlrmt.lib ..\tmp\ga_sandbox\lib_win32
copy c:\lib32\antlrdmt.lib ..\tmp\ga_sandbox\lib_win32

cd ..\tmp
del ga_sandbox_win32_binary_libraries.tar
del ga_sandbox_win32_binary_libraries.tar.gz
tar cf ga_sandbox_win32_binary_libraries.tar ga_sandbox
gzip -9 ga_sandbox_win32_binary_libraries.tar
move ga_sandbox_win32_binary_libraries.tar.gz ..
del /Q ga_sandbox
cd ..
del /Q tmp
cd ..\ga_sandbox