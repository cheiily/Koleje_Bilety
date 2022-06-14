//
// Created by Kusidel on 20.05.2022.
//

#include "UnitHierarchy/DieselExpress.h"



DieselExpress::DieselExpress(const std::string & unitId, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer,
                             int manufacturingYear, int maxVelocity, long mileage, int capacity, const std::string & carrier, int locomotiveQuantity,
                             int carQuantity, double engineDisplacement)
               : Express(unitId, unitName, countryOfOrigin, manufacturer, manufacturingYear, maxVelocity, mileage, capacity, carrier, locomotiveQuantity, carQuantity)
               , engineDisplacement(engineDisplacement)
{
    if (engineDisplacement <= 0) throw NegativeNumericException(typeid(this).name(), quote(engineDisplacement));
}

DieselExpress::~DieselExpress() = default;

double DieselExpress::getEngineDisplacement() const {
    return engineDisplacement;
}

std::string DieselExpress::getUnitInfo() const {
    return Express::getUnitInfo()+" | Engine displacement: "+ std::to_string(getEngineDisplacement());
}

void DieselExpress::setEngineDisplacement(double engineDisplacement) {
    if (engineDisplacement <= 0) throw NegativeNumericException(typeid(this).name(), quote(engineDisplacement));
    this->engineDisplacement = engineDisplacement;
}

