@echo off
REM Makefile.bat for CityPowerManager

set PROJECT_NAME=CityPowerManager

REM Set the compiler and standard
set CXX=g++
set CXXFLAGS=-std=c++17

REM Include directories
set INCLUDE_DIRS=-Iinclude

REM Source files
set SRC=src\main.cpp src\core\app.cpp src\core\billing_system.cpp src\models\commercial_subscriber.cpp src\models\industrial_subscriber.cpp src\models\residential_subscriber.cpp src\models\subscriber.cpp src\models\tariff.cpp src\utils\file_io.cpp

REM Output directory
set OUT_DIR=build

REM Create output directory if it doesn't exist
if not exist %OUT_DIR% (
    mkdir %OUT_DIR%
)

REM Compile and link
%CXX% %CXXFLAGS% %INCLUDE_DIRS% %SRC% -o %OUT_DIR%\%PROJECT_NAME%

if %ERRORLEVEL% neq 0 (
  echo Build failed!
  exit /b %ERRORLEVEL%
) else (
  echo Build succeeded!
  echo Check the ./build for the .exe
)
