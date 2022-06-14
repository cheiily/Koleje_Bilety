//
// Created by student on 20.05.2022.
//

#include "UnitHierarchy/Tram.h"

Tram::Tram(const std::string & unitId, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer,
           int manufacturingYear, int maxVelocity, long mileage, int capacity, const std::string & city, bool composite)
           : UrbanUnit(unitId, unitName, countryOfOrigin, manufacturer, manufacturingYear, maxVelocity, mileage, capacity, city)
           , composite(composite)
           {}

bool Tram::isComposite() const {
    return composite;
}

void Tram::setComposite(bool composite) {
    this->composite = composite;
}

std::string Tram::getUnitInfo() const {
    return UrbanUnit::getUnitInfo() + (isComposite() ? " | Composite" : " | Singular ");
}
