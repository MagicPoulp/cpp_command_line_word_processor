#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "Processor.hpp"
#include "Enums.hpp"

using namespace std;

#define GIGANTIC_LINE_SIZE 3000 * 4 // 4 bytes max per char in UTF 4
#define AVERAGE_WORD_SIZE 30
#define NUM_MAX_WORDS 200

// we could optimize by streaming
// to simplify we save the input in memory
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
        inputData.push_back(word);
      }
    }
    file.close();
  } // else report error

  //processTransformSteps(inputData);

  file.open(output, ios::out | std::ios::trunc);
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

// it is a best practice to reuse the memory instead of dupliocating it for the result
void Processor::processTransformSteps(vector<string>& inputData) {
  for (auto& step : transformSteps) {
    processOneTransformStep(inputData, step);
  }
}

void Processor::processOneTransformStep(vector<string>& inputData, processor_step step) {
  switch (step) {
  case SORT_ASC:
    cout << "sort ascending" << endl;
    sort(inputData.begin(), inputData.end());
    break;
  case SORT_DESC:
    cout << "sort descending" << endl;
    sort(inputData.begin(), inputData.end(), std::greater<string>());
    break;
  case DISTINCT:
    cout << "filter out duplicates" << endl;
    // 3 ways work better depending on number of duplicates
    // https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
    // Once all duplicate elements are shifted at one end of vector, then delete them using the vector::erase()
    sort(inputData.begin(), inputData.end());
    inputData.erase(unique(inputData.begin(), inputData.end()), inputData.end() );
    break;
  }
}
