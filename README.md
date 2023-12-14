#Author

Thierry Vilmart

December 2023

# Summary

A simple command line program in C++.
It parses options and sorts or filters words given in input.

# How to run

sudo apt-get install libboost-all-dev build-essential g++
g++ Main.cpp -o processor -std=c++11 -Iinclude/boost_1_82_0 -lboost_program_options
ou make
./processor --help
ou make help
./processor -i input.txt -o output.txt --sort-word-size --filter-duplicates
ou make run
