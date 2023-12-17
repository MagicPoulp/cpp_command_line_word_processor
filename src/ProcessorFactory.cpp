# include "ProcessorFactory.hpp"
# include "ProcessorBuilder.hpp"
# include "Processor.hpp"
# include "Enums.hpp"

Processor ProcessorFactory::create(bool sortWordSize, sort_dir sortingDirection, bool filterDuplicates) {
  ProcessorBuilder result;
  if (filterDuplicates) {
    result.distinct();
  }
  if (sortWordSize) {
    // 2 parameters become one algo step
    result.sort(sortingDirection);
  }
  return result.build();
}
