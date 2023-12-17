#include <algorithm>
#include "ProcessorBuilder.hpp"
#include "Processor.hpp"
#include "Enums.hpp"

// in the Command design pattern, we specify first what we will do
void ProcessorBuilder::sort(sort_dir direction) {
  std::vector<processor_step>::iterator itSortStep = std::find_if(transformSteps.begin(), transformSteps.end(),
                                  [](processor_step step) { return step == SORT_ASC || step == SORT_DESC; });
  if (itSortStep != transformSteps.end()) {
    transformSteps.erase(itSortStep);
  }
  switch(direction) {
  case ASC:
    transformSteps.push_back(SORT_ASC);
    break;
  case DESC:
    transformSteps.push_back(SORT_DESC);
    break;
  }
}

void ProcessorBuilder::distinct() {
  transformSteps.push_back(DISTINCT);
}

Processor ProcessorBuilder::build() {
  // having the sorting step before makes distinct faster
  std::vector<processor_step>::iterator itSortStep = std::find_if(transformSteps.begin(), transformSteps.end(),
                                                       [](processor_step step) { return step == SORT_ASC || step == SORT_DESC; });
  if (itSortStep != transformSteps.end()) {
    std::iter_swap(transformSteps.begin(), itSortStep);
  }
  return Processor(transformSteps);
}
