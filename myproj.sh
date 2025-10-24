#!/bin/bash

g++ -std=c++17 *.cpp -o executables/myprogram
echo "Successfully compiled all cpp files."
./executables/myprogram
echo "Program Terminated."
