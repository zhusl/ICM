@echo off
cd source
g++ -std=c++11 main.cpp ast.cpp objectdata.cpp tostring.cpp match.cpp parser.cpp -I..\include -o main && main
pause
