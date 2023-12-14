#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <unordered_set>
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

  processTransformSteps(inputData);

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

// anonymous namespace makes it local
namespace
{
  // adding sorting for equal size creates unique results
  bool compareStringSize(string s1, string s2) { return s1.size() < s2.size() || (s1.size() == s2.size() && s1 < s2); }
  bool compareStringSizeDesc(string s1, string s2) { return !compareStringSize(s1, s2); }
}

// the strategy pattern is used here, to decouple the algorithm from the client, and change teh algorithm at runtime.
// but the patterm is not fully used since we do not have separate classes for each strategy
// This allows to have less strategies to support (one for each combination of sort, sort descending, filter duplicates).
// We could make classes to make sure evolutions do not touch classes, and do not break SOLID's Open/Close
void Processor::processOneTransformStep(vector<string>& inputData, processor_step step) {
  switch (step) {
  case SORT_ASC:
    cout << "sort ascending" << endl;
    sort(inputData.begin(), inputData.end(), ::compareStringSize);
    break;
  case SORT_DESC:
    cout << "sort descending" << endl;
    sort(inputData.begin(), inputData.end(), ::compareStringSizeDesc);
    break;
  case DISTINCT:

    // if already sorted ascending or descending
    if (find_if(transformSteps.begin(), transformSteps.end(), [](processor_step s) { return s == SORT_ASC || s == SORT_DESC; } ) != transformSteps.end()) {
      // Strategy 1, distinct when the data is presorted (ascending or dscending, same algo)
      cout << "Strategy 1 - filter out duplicates with presorting" << endl;
      // 3 ways to remove duplicates with presorting work better depending on number of duplicates
      // https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
      // Once all duplicate elements are shifted at one end of vector, then delete them using the vector::erase()

      // this does not work on unsorted data, because unique() needs consecutive duplicates to remove them
      inputData.erase(unique(inputData.begin(), inputData.end()), inputData.end() );
    }
    else
      {
        // Strategy 2, distinct when the data is not presorted
        cout << "Strategy 2 - filter out duplicates without presorting" << endl;
        // https://stackoverflow.com/questions/49863158/c-remove-duplicate-values-from-a-vector-without-sorting
        std::unordered_set<string> set;
        for (auto it = inputData.begin(); it != inputData.end(); ) {
          if (set.find(*it) == set.end()) {
            set.insert(*it);
            it++;
          }
          else {
            it = inputData.erase(it);
          }
        }
      }
    break;
  }
}
