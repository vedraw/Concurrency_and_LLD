#include "StrategyFactory.h"

IAssignmentStrategy* StrategyFactory::createStrategy(StrategyType type) {
    switch (type) {
        case StrategyType::FirstAvailable:
            return new FirstAvailable();
        default:
            return nullptr;
    }
}
