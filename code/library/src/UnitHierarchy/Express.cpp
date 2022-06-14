//
// Created by Kusidel on 20.05.2022.
//

#include "UnitHierarchy/Express.h"

Express::Express(const std::string & unitID, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer,
                 int manufacturingYear, int maxVelocity, long mileage, int capacity, const std::string & carrier, int locomotiveQuantity, int carQuantity)
                 : IntercityUnit(unitID, unitName, countryOfOrigin, manufacturer, manufacturingYear, maxVelocity, mileage, capacity, carrier)
                 , locomotiveQuantity(locomotiveQuantity), carQuantity(carQuantity)
{
    if (locomotiveQuantity <= 0) throw NegativeNumericException(typeid(this).name(), quote(locomotiveQuantity));
    if (carQuantity <= 0) throw NegativeNumericException(typeid(this).name(), quote(carQuantity));
}

Express::~Express() {}

int Express::getLocomotiveQuantity() const {
    return locomotiveQuantity;
}

int Express::getCarQuantity() const {
    return carQuantity;
}

std::string Express::getUnitInfo() const {
    std::ostringstream ss;
    ss << IntercityUnit::getUnitInfo();
    ss <<  + " | Locomotive quantity: " << getLocomotiveQuantity() << " | Car quantity: " << getCarQuantity();
    return ss.str();
}

void Express::setLocomotiveQuantity(int locomotiveQuantity) {
    if (locomotiveQuantity <= 0) throw NegativeNumericException(typeid(this).name(), quote(locomotiveQuantity));
    this->locomotiveQuantity = locomotiveQuantity;
}

void Express::setCarQuantity(int carQuantity) {
    if (carQuantity <= 0) throw NegativeNumericException(typeid(this).name(), quote(carQuantity));
    this->carQuantity = carQuantity;
}
