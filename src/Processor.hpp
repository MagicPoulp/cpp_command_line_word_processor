#pragma once

#include <vector>
#include <string>
#include "Enums.hpp"

class Processor {
public:
  Processor(std::vector<processor_step> steps);
  void process(const std::string& input, const std::string& output);
};
