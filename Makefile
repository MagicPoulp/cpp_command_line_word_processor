all:
	g++ src/Main.cpp src/ProcessorFactory.cpp src/ProcessorBuilder.cpp src/Processor.cpp -o processor -std=c++11 -Isrc -Iinclude/boost_1_82_0 -lboost_program_options

help:
	./processor --help

run:
	./processor -i input.txt -o output1_sorted.txt --sort-word-size
	./processor -i input.txt -o output2_sorted_desc.txt --sort-word-size-desc
	./processor -i input.txt -o output3_filtered.txt --filter-duplicates
	./processor -i input.txt -o output4_sorted_filtered.txt --sort-word-size --filter-duplicates
	./processor -i input.txt -o output5_sorted_desc_filtered.txt --sort-word-size-desc --filter-duplicates
