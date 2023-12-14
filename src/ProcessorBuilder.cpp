#include "ProcessorBuilder.hpp"
#include "Processor.hpp"
#include "Enums.hpp"

// in the Command design pattern, we specify first what we will do
void ProcessorBuilder::sort(sort_dir direction) {
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
  return Processor(transformSteps);
}
