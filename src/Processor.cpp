#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <boost/algorithm/string.hpp>
#include "Processor.hpp"
#include "Enums.hpp"

using namespace std;

#define GIGANTIC_LINE_SIZE 3000 * 4 // 4 bytes max per char in UTF 4
#define AVERAGE_WORD_SIZE 30
#define NUM_MAX_WORDS 200


void Processor::process(const string& input, const string& output) {
  vector<string> inputData;
  inputData.reserve(round(1.3 * AVERAGE_WORD_SIZE * NUM_MAX_WORDS));
  fstream file;

  file.open(input, ios::in);
  if (file.is_open()) {
    string tp;
    // reserving avoid heap allocation and speeds up
    tp.reserve(GIGANTIC_LINE_SIZE);
    while(getline(file, tp)){
      boost::replace_all(tp, "'", " ");
      boost::replace_all(tp, ".", "");
      stringstream ss(tp);
      string word;
      while (ss >> word) {
        inputData.push_back(tp);
      }
    }
    file.close();
  } // else report error

  file.open(output, ios::out);
  if(file.is_open()) {
    int i = 0;
    for (auto& word : inputData) {
      if (i != 0) {
        file << " ";
      }
      file << word;
      i += 1;
    }
  } // else report error
  file.close();
}
