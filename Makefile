all:
	g++ Main.cpp -o processor -std=c++11 -Iinclude/boost_1_82_0 -lboost_program_options
