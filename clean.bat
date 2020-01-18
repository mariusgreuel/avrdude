@echo off
rmdir /s /q ".vs" >nul 2>nul

rmdir /s /q "Debug" >nul 2>nul
rmdir /s /q "Release" >nul 2>nul
rmdir /s /q "x64" >nul 2>nul

rmdir /s /q "external\libelf\Debug" >nul 2>nul
rmdir /s /q "external\libelf\Release" >nul 2>nul
rmdir /s /q "external\libelf\x64" >nul 2>nul

rmdir /s /q "external\libhidapi\Debug" >nul 2>nul
rmdir /s /q "external\libhidapi\Release" >nul 2>nul
rmdir /s /q "external\libhidapi\x64" >nul 2>nul

rmdir /s /q "external\libusb\Debug" >nul 2>nul
rmdir /s /q "external\libusb\Release" >nul 2>nul
rmdir /s /q "external\libusb\x64" >nul 2>nul

rmdir /s /q .deps
rmdir /s /q .libs
rmdir /s /q autom4te.cache
rmdir /s /q m4

del ac_cfg.h
del ac_cfg.h.in
del aclocal.m4
del avrdude
del avrdude.conf
del avrdude.conf.tmp
del avrdude.spec
del compile
del config.guess
del config.log
del config.status
del config.sub
del config_gram.c
del config_gram.h
del configure
del depcomp
del INSTALL
del install-sh
del lexer.c
del libtool
del ltmain.sh
del Makefile
del Makefile.in
del mdate-sh
del mkinstalldirs
del missing
del stamp-h.in
del stamp-h1
del texinfo.tex
del y.output
del y.tab.h
del ylwrap
del *.o
del *.lo
del *.a
del *.la
del *.diff
del *.patch
