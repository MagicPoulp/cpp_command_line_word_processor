// https://www.boost.org/doc/libs/1_55_0/libs/program_options/example/real.cpp

// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/program_options.hpp>
#include <iostream>

#include "Processor.hpp"
#include "ProcessorFactory.hpp"
#include "Enums.hpp"

namespace po = boost::program_options;

using namespace std;

int main(int argc, char* argv[])
{
  try {
    string inputFile;
    string outputFile;
    po::options_description desc("Usage:\n"
                                 "./processor -i input.txt -o output.txt --sort-word-size --filter-duplicates\n\n"
                                 "Options");
    desc.add_options()
      ("help,h", "print usage message")
      ("input,i", po::value<std::string>(&inputFile)->required(), "pathname for input")
      ("output,o", po::value<std::string>(&outputFile)->required(), "pathname for output")
      ("sort-word-size", "sort by word size ascending")
      ("sort-word-size-desc", "sort by word size descending")
      ("filter-duplicates", "filter out duplicated words")
      ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {
      cout << desc << endl;
      return 0;
    }
    po::notify(vm);

    vector<bool> listAlgoOptions;
    bool sortWordSize = vm.count("sort-word-size") != 0;
    bool sortWordSizeDesc = vm.count("sort-word-size-desc") != 0;
    bool filterDuplicates = vm.count("filter-duplicates") != 0;
    if (sortWordSize && sortWordSizeDesc) {
      cout << "Error. We cannot sort both ascending or descending" << endl << endl;
      cout << desc << endl;
      return 1;
    }
    listAlgoOptions.push_back(sortWordSize);
    listAlgoOptions.push_back(sortWordSizeDesc);
    listAlgoOptions.push_back(filterDuplicates);
    if (find(listAlgoOptions.begin(), listAlgoOptions.end(), true) == listAlgoOptions.end()) {
      cout << "Error. At least one processing option is required." << endl << endl;
      cout << desc << endl;
      return 1;
    }
    cout << "input: " << inputFile << endl;
    cout << "output: " << outputFile << endl;
    cout << "sortWordSize: " << std::boolalpha << sortWordSize << endl;
    cout << "filterDuplicates: " << std::boolalpha << filterDuplicates << endl << endl;

    // factory pattern is used to allow subclasses to change behavior, or to defer creation
    // strategy pattern is used so that we do not break SOLID's open/close when algorithms evolve, and object data does not matter
    // we do not use chain of responsibility pattern, because we do not need to decouple sender and receiver like in a backend,
    // and we we do not have multiple receivers (like Views on iOS where the pattern is famously used)
    // builder pattern is used in ProcessorFactory
    // command patter is used in the ProcessorBuilder

    // strategy pattern
    // https://en.wikipedia.org/wiki/Strategy_pattern
    // factory pattern
    // https://en.wikipedia.org/wiki/Factory_method_pattern

    ProcessorFactory factory;
    Processor processor = factory.create(sortWordSize || sortWordSizeDesc, sortWordSize ? ASC : DESC, filterDuplicates);
    try {
      processor.process(inputFile, outputFile);
    }
    // TODO list relevant exceptions, file access, etc
    catch(exception& e) {
      cerr << "Error" << endl;
      cerr << e.what() << endl;
    }
  }
  catch(exception& e) {
    cerr << "Error" << endl;
    cerr << e.what() << endl;
  }
}
