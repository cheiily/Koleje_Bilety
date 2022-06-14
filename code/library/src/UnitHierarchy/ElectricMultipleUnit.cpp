//
// Created by Kusidel on 20.05.2022.
//

#include "UnitHierarchy/ElectricMultipleUnit.h"

ElectricMultipleUnit::ElectricMultipleUnit(const std::string & unitID, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer,
                                           int manufacturingYear, int maxVelocity, long mileage, int capacity, const std::string & carrier, int unitQuantity)
                                           : IntercityUnit(unitID, unitName, countryOfOrigin, manufacturer, manufacturingYear, maxVelocity, mileage, capacity, carrier)
                                           , emuUnitQuantity(unitQuantity)
{
    if (unitQuantity <= 0) throw NegativeNumericException(typeid(this).name(), quote(unitQuantity));
}

ElectricMultipleUnit::~ElectricMultipleUnit() = default;


int ElectricMultipleUnit::getUnitQuantity() const {
    return emuUnitQuantity;
}

std::string ElectricMultipleUnit::getUnitInfo() const {
    std::ostringstream ss;
    ss << IntercityUnit::getUnitInfo();
    ss << " | Number of EMU units: " << getUnitQuantity();
    return ss.str();
}

void ElectricMultipleUnit::setUnitQuantity(int unitQuantity) {
    if (unitQuantity <= 0) throw NegativeNumericException(typeid(this).name(), quote(unitQuantity));
    this->emuUnitQuantity = unitQuantity;
}



