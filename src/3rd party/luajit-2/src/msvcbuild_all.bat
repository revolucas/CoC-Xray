@echo off

if not defined DevEnvDir (
  if defined VS140COMNTOOLS ( 
    set setup_env=call "%VS140COMNTOOLS%\..\..\VC\vcvarsall.bat"
  ) else (
    echo "VS140COMNTOOLS is not defined, aborting."
    exit /b 1
  )
)
echo * Building LuaJIT x86...
%setup_env% x86
call msvcbuild.bat x86
if errorlevel 1 goto :fail

echo * Building LuaJIT x64...
%setup_env% x86_amd64
call msvcbuild.bat x64
if errorlevel 1 goto :fail

goto :end
:fail
echo Build failed.
:end
