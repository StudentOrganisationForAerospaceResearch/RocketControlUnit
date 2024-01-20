::
:: FILE: GenerateProto.bat
:: BRIEF: This is a batch file to generate the C++ and Python code from the .proto files.
:: AUTHOR: Christopher Chan (cjchanx)
::
@echo off
echo ** Generating Protocol Buffers **
protoc --plugin=protoc-gen-eams=protoc-gen-eams.bat --eams_out=_C++ *.proto
protoc --pyi_out=_Python --python_out=_Python *.proto
protoc --pyi_out=PythonTestProject --python_out=PythonTestProject *.proto

echo ** C++ File Cleanup **
cd _C++
del *.hpp
ren *.h *.hpp
ren CoreProto.hpp CoreProto.h

echo.
echo 	  ** Done! **
PAUSE