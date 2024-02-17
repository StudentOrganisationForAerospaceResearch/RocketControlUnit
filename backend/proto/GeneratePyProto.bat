::
:: FILE: GenerateProto.bat
:: BRIEF: This is a batch file to generate the C++ and Python code from the .proto files.
:: AUTHOR: Christopher Chan (cjchanx)
::
@echo off
echo ** Generating Protocol Buffers Python Files **

:: Check if Python directory exists, if not create it
if not exist "Python\" (
    mkdir Python
)

::protoc --plugin=protoc-gen-eams=protoc-gen-eams.bat --eams_out=_C++ *.proto
::protoc --pyi_out=_Python --python_out=_Python *.proto
protoc --pyi_out=Python --python_out=Python *.proto

::echo ** C++ File Cleanup **
::cd _C++
::del *.hpp
::ren *.h *.hpp
::ren CoreProto.hpp CoreProto.h

echo.
echo 	  ** Done! **
PAUSE