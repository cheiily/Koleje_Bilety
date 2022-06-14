//
// Created by student on 20.05.2022.
//

#include "UnitHierarchy/Railbus.h"

Railbus::Railbus(const std::string & unitId, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer,
                 int manufacturingYear, int maxVelocity, long mileage, int capacity, const std::string & city)
                 : UrbanUnit(unitId, unitName, countryOfOrigin, manufacturer, manufacturingYear, maxVelocity, mileage, capacity, city)
                 {}

std::string Railbus::getUnitInfo() const {
    return UrbanUnit::getUnitInfo();
}
