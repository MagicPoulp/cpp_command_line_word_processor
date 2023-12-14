#pragma once

#include <vector>
#include <string>
#include "Enums.hpp"

class Processor {
private:
  std::vector<processor_step> steps;

public:
  Processor(std::vector<processor_step> steps2) : steps(steps2) {}
  void process(const std::string& input, const std::string& output);
};
