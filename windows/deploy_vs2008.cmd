@echo off

rmdir /S /Q ..\lib
mkdir ..\lib

copy /Y vcpp2008\Release\websocketpp.lib ..\lib
copy /Y vcpp2008\Debug\websocketppd.lib ..\lib

rmdir /S /Q ..\include
mkdir ..\include

xcopy /Q /E /I /C /H /R /Y ..\src ..\include
copy /Y vcpp2008\stdint.h ..\include

cd ..\include

del /Q SConscript
del /Q *.cpp
del /Q base64\*.cpp
del /Q md5\*.c
del /Q messages\*.cpp
del /Q processors\*.cpp
del /Q processors\*.cpp
del /Q rng\*.cpp
del /Q sha1\Makefile*
del /Q sha1\*.cpp
rmdir /S /Q ssl
