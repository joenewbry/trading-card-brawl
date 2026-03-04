@echo off
setlocal enabledelayedexpansion

set PROJECT_NAME=TradingCardBrawl
set UPROJECT_PATH=%~dp0%PROJECT_NAME%.uproject

set UE_ROOT_1=C:\Epic\UE_5.3
set UE_ROOT_2=%USERPROFILE%\UnrealEngine
set UE_ROOT_3=C:\opt\UnrealEngine

set UE_ROOT=
if exist "%UE_ROOT_1%" set UE_ROOT=%UE_ROOT_1%
if "%UE_ROOT%"=="" if exist "%UE_ROOT_2%" set UE_ROOT=%UE_ROOT_2%
if "%UE_ROOT%"=="" if exist "%UE_ROOT_3%" set UE_ROOT=%UE_ROOT_3%

if "%UE_ROOT%"=="" (
  echo Unreal Engine 5.3 was not found in these locations:
  echo   - %UE_ROOT_1%
  echo   - %UE_ROOT_2%
  echo   - %UE_ROOT_3%
  echo Download UE5.3 from: https://www.unrealengine.com/en-US/download
  exit /b 1
)

set UAT_SCRIPT=%UE_ROOT%\Engine\Build\BatchFiles\RunUAT.bat
if not exist "%UAT_SCRIPT%" (
  echo Found Unreal Engine at "%UE_ROOT%" but RunUAT.bat was not found.
  echo Please verify your UE5.3 installation and try again.
  exit /b 1
)

echo Using Unreal Engine at: %UE_ROOT%
echo Starting WebGL build for %PROJECT_NAME%...

call "%UAT_SCRIPT%" BuildCookRun ^
  -project="%UPROJECT_PATH%" ^
  -platform=HTML5 ^
  -clientconfig=Shipping ^
  -build -cook -stage -pak -archive

endlocal
