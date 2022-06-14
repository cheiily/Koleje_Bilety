//
// Created by Kusidel on 19.05.2022.
//

#include "UnitHierarchy/UrbanUnit.h"

UrbanUnit::UrbanUnit(const std::string & unitID, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer, int manufacturingYear,
                     int maxVelocity, long mileage, int capacity, const std::string & city)
                     : PassengerUnit(unitID, unitName, countryOfOrigin, manufacturer,
                                     manufacturingYear, maxVelocity, mileage, capacity)
                     , city(city)
                     {}

UrbanUnit::~UrbanUnit() {}

const std::string & UrbanUnit::getCity() const {
    return city;
}

std::string UrbanUnit::getUnitInfo() const {
    return PassengerUnit::getUnitInfo() + " | City: " + getCity();
}

void UrbanUnit::setCity(const std::string & newCity) {
    city = newCity;
}



