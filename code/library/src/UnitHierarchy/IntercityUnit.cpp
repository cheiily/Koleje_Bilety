//
// Created by Kusidel on 19.05.2022.
//

#include "UnitHierarchy/IntercityUnit.h"

IntercityUnit::IntercityUnit(const std::string & unitID, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer,
                             int manufacturingYear, int maxVelocity, long int mileage, int capacity, const std::string & carrier)
                             : PassengerUnit::PassengerUnit(unitID, unitName, countryOfOrigin, manufacturer, manufacturingYear, maxVelocity, mileage, capacity)
                             , carrier(carrier)
                             {}

IntercityUnit::~IntercityUnit() = default;

const std::string & IntercityUnit::getCarrier() const {
    return carrier;
}

std::string IntercityUnit::getUnitInfo() const {
    return PassengerUnit::getUnitInfo() + " | Carrier: " + getCarrier();
}

void IntercityUnit::setCarrier(const std::string & carrier) {
    this->carrier = carrier;
}



