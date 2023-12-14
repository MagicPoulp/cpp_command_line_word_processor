#pragma once

#include "Processor.hpp"
#include "Enums.hpp"

class ProcessorFactory {
public:
  Processor create(bool sortWordSize, sort_dir sortDirection, bool filterDuplicates);
};
