::
:: FILE: QuickInstall.bat
:: BRIEF: This is a batch file to install the required software to generate the C++ and Python code from the .proto files.
:: AUTHOR: Christopher Chan (cjchanx)
::
@echo off
echo Note: Please run this script in administrator mode, it may cause issues with the protoc install otherwise
echo.

echo Setting up Chocolatey...
echo Note: You may have to run this script twice if you did not have Chocolatey installed...
echo.
@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "[System.Net.ServicePointManager]::SecurityProtocol = 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"

echo Setting up Python...
python --version
if ERRORLEVEL 1 C:\ProgramData\Chocolatey\bin\choco.exe install python
call refreshenv
pip install protobuf

echo Setting up ProtocolBuffers...
C:\ProgramData\Chocolatey\bin\choco.exe install protoc --version=3.6.1
call refreshenv

echo Setting up EmbeddedProto...
cd EmbeddedProto
python setup.py

pause
