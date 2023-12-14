#pragma once

#include <vector>
#include <string>
#include "Enums.hpp"

class Processor {
private:
  std::vector<processor_step> transformSteps;

public:
  Processor(std::vector<processor_step> transformSteps2) : transformSteps(transformSteps2) {}
  void process(const std::string& input, const std::string& output);
  void processTransformSteps(std::vector<std::string>& inputData);
  void processOneTransformStep(std::vector<std::string>& inputData, processor_step step);
};

