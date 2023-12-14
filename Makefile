all:
	g++ Main.cpp -o processor -std=c++11 -Iinclude/boost_1_82_0 -lboost_program_options

help:
	./processor --help

run:
	./processor -i input.txt -o output1_same.txt
#	./processor -i input.txt -o output2_sorted.txt --sort-word-size
#	./processor -i input.txt -o output3_filtered.txt --filter-duplicates
#	./processor -i input.txt -o output4_sorted_filtered.txt --sort-word-size --filter-duplicates
