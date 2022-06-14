//
// Created by student on 01.06.2022.
//

#include "Managers/LineManager.h"

LinePtr LineManager::getLine(const std::string &lineId) const {
    return registry.findById(lineId);
}

std::vector<LinePtr> LineManager::findLines(const LinePredicate & matchingMethod) const {
    auto f = [matchingMethod](const LinePtr & line) -> bool {
        return (matchingMethod(line) && line->isOpen());
    };
    return registry.findBy(f);
}

std::vector<LinePtr> LineManager::findAllLines() const {
    return findLines([](const LinePtr & line) -> bool { return true; });
}

LinePtr LineManager::addNewLine(const std::string &lineId, const std::vector<NodePtr> &route, const UnitPtr & assignedUnit) {
    LinePtr ptr = getLine(lineId);
    if(ptr!= nullptr) return ptr;

    ptr = std::make_shared<Line>(lineId, route, assignedUnit);
    registry.add(ptr);

    return ptr;
}

void LineManager::closeLine(const LinePtr &line) {
    LinePtr found = getLine(line->getID());
    if (found != nullptr) {
        found->setOpen(false);
    }
}

void LineManager::beginLineRenovation(const LinePtr & line, const std::vector<std::string> & renovatedSegment) {
    LinePtr found = getLine(line->getID());
    if (found != nullptr) {
        auto tmp = renovatedSegment;

        for (auto & passed : tmp) {
            if (!found->hasNode(passed)) {
                tmp.erase(std::remove(tmp.begin(), tmp.end(), passed), tmp.end());
            }
        }

        if (tmp.empty()) throw CollectionMismatchException(typeid(this).name(), quote(renovatedSegment));

        found->setRenovated(true);
        found->setRenovatedSegment(renovatedSegment);
    }
}

void LineManager::finishLineRenovation(const LinePtr &line) {
    LinePtr found = getLine(line->getID());
    if (found != nullptr) {
        found->setRenovated(false);
        found->setRenovatedSegment({});
    }
}



