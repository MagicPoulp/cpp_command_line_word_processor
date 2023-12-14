#pragma once

#include <vector>

#include "Processor.hpp"
#include "Enums.hpp"

class ProcessorBuilder {
private:
  std::vector<processor_step> transformSteps;

public:
  void sort(sort_dir direction);
  void distinct();
  Processor build();
};
