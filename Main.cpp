// https://www.boost.org/doc/libs/1_55_0/libs/program_options/example/real.cpp

// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/program_options.hpp>
using namespace boost::program_options;

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    try {
        string ofile;
        string macrofile, libmakfile;
        bool t_given = false;
        bool b_given = false;
        string mainpackage;
        string depends = "deps_file";
        string sources = "src_file";
        string root = ".";

        options_description desc("Usage:\n"
                                 "./processor -i input.txt -o output.txt --sort-word-size --filter-duplicates\n\n"
                                 "Options");
        desc.add_options()
        ("help,h", "print usage message")
        ("input,i", value(&ofile), "pathname for input")
        ("output,o", value(&ofile), "pathname for output")
        ("sort-word-size", "sort by word size")
        ("filter-duplicates", "filter out duplicated words")
        ;

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }
        //cout << "two = " << vm["two"].as<bool>() << "\n";
    }
    catch(exception& e) {
        cerr << e.what() << "\n";
    }
}
