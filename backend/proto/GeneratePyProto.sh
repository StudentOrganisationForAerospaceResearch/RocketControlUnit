#!/bin/bash
# FILE: GenerateProto.sh
# BRIEF: This is a shell script to generate the C++ and Python code from the .proto files.
# AUTHOR: Christopher Chan (cjchanx)

echo "** Generating Protocol Buffers Python Files **"

# Check if Python directory exists, if not create it
if [ ! -d "Python" ]; then
  mkdir Python
fi

#protoc --plugin=protoc-gen-eams=protoc-gen-eams.bat --eams_out=_C++ *.proto
#protoc --pyi_out=_Python --python_out=_Python *.proto
protoc --pyi_out=Python --python_out=Python ./*.proto

#echo "** C++ File Cleanup **"
#cd _C++
#rm *.hpp
#mv *.h *.hpp
#mv CoreProto.hpp CoreProto.h

echo
echo "** Done! **"
read -p "Press any key to continue... " -n1 -s