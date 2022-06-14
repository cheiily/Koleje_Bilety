//
// Created by student on 20.05.2022.
//

#include "UnitHierarchy/ElectricExpress.h"



ElectricExpress::~ElectricExpress() {}

ElectricExpress::ElectricExpress(const std::string & unitId, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer,
                                 int manufacturingYear, int maxVelocity, long mileage, int capacity, const std::string & carrier, int locomotiveQuantity, int carQuantity, double supplyVoltage)
                   : Express(unitId, unitName, countryOfOrigin, manufacturer, manufacturingYear, maxVelocity, mileage, capacity, carrier, locomotiveQuantity, carQuantity)
                   , supplyVoltage(supplyVoltage)
{
    if (supplyVoltage <= 0) throw NegativeNumericException(typeid(this).name(), quote(supplyVoltage));
}

double ElectricExpress::getSupplyVoltage() const {
    return supplyVoltage;
}

std::string ElectricExpress::getUnitInfo() const {
    std::ostringstream ss;
    ss << Express::getUnitInfo();
    ss << " | Supply voltage: " << getSupplyVoltage();
    return ss.str();
}

void ElectricExpress::setSupplyVoltage (double supplyVoltage) {
    if (supplyVoltage <= 0) throw NegativeNumericException(typeid(this).name(), quote(supplyVoltage));
    this->supplyVoltage = supplyVoltage;
}

