@echo off
REM *BATCH**************************************************************
REM  This file was generated by Design Tool a product of: 
REM     ARC International  
REM     http://www.ARC.com/         
REM                            
REM     Fri Jun 08 11:29:32 2007
REM 
REM     Copyright (c) ARC International  
REM     All rights reserved    
REM 
REM     This software embodies materials and concepts which are
REM     confidential to ARC International and is made
REM     available solely pursuant to the terms of a written license
REM     agreement with ARC International.
REM 
REM ******************************************************************/
REM   Generic Batch file used to compile design 
REM
set mqx_old_path=%path%

if     .%1 == . goto syntax
if     .%2 == . goto syntax
if not .%4 == . goto syntax

if .%3 == .little set mqx_lib_ext=l
if .%3 == .LITTLE set mqx_lib_ext=l
if .%3 == .big    set mqx_lib_ext=b
if .%3 == .BIG    set mqx_lib_ext=b
if .%3 == .       set mqx_lib_ext=
set mqx=%mqx_root%\lib\%1%mqx_lib_ext%.%2

if not exist %mqx%\nul goto syntax
if not exist %mqx%\bspsetup.bat goto syntax
if not exist %MQX_BAT_ROOT%\%2.bat goto notsup

goto compile
:syntax
echo Syntax:
echo.
echo    GO (BSP) (COMP) [OPT]
echo.
echo Compile the test program for BSP with compiler COMP
echo.
echo eg. go sdsim360 sds
echo     go deevb285 arm big
echo.
goto clean

:notsup
echo BSP %1% is not supported with compiler %2%.
echo.
goto clean

REM
REM Start mqx_compiling
REM
:compile

set mqx_proj=hello7
set mqx_comp=%2
set mqx_bsp=%1

REM this sets up mqx_proc and bsp_entry
call %mqx%\bspsetup

if .%mqx_proc% == . goto syntax

REM Set up compiler environment variables for the PSP
REM this sets up mqx_proc, mqx_psp, mqx_aext and mqx_objext
call %MQX_BAT_ROOT%\%mqx_comp% %mqx_proc% %3
if .%mqx_psp% == . goto notsup

if not exist %mqx_bsp%%mqx_lib_ext%.%mqx_comp%\nul mkdir %mqx_bsp%%mqx_lib_ext%.%mqx_comp%
cd %mqx_bsp%%mqx_lib_ext%.%mqx_comp%

if exist errors del errors

call %MQX_BAT_ROOT%\%mqx_comp% start

call %MQX_BAT_ROOT%\%mqx_comp% comp .. ttl
call %MQX_BAT_ROOT%\%mqx_comp% comp .. hello7
call %MQX_BAT_ROOT%\%mqx_comp% comp .. hello
call %MQX_BAT_ROOT%\%mqx_comp% comp .. isr

REM
REM Build HEX image
REM

call %MQX_BAT_ROOT%\%mqx_comp% link
call %MQX_BAT_ROOT%\%mqx_comp% clean

cd ..

REM
REM Clean up environment
REM
:clean

set mqx_proj=
set mqx_comp=
set mqx_bsp=
set mqx_proc=
set bsp_entry=
set mqx_lib_ext=

set path=%mqx_old_path%
set mqx_old_path=

:end
REM EOF
