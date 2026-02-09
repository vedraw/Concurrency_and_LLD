#ifndef STRATEGYFACTORY_H
#define STRATEGYFACTORY_H

#include "IAssignmentStrategy.h"
#include "FirstAvailable.h"

enum class StrategyType {
    FirstAvailable
};

class StrategyFactory {
public:
    static IAssignmentStrategy* createStrategy(StrategyType type);
};

#endif
