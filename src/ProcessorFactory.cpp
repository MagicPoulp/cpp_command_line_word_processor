# include "ProcessorFactory.hpp"
# include "ProcessorBuilder.hpp"
# include "Processor.hpp"
# include "Enums.hpp"

Processor ProcessorFactory::create(bool sortWordSize, sort_dir sortingDirection, bool filterDuplicates) {
  ProcessorBuilder result;
  if (sortWordSize) {
    // 2 parameters become one algo step
    result.sort(sortingDirection);
  }
  // having the sorting stepbefore makes distinct faster
  if (filterDuplicates) {
    result.distinct();
  }
  return result.build();
}
