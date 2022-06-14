//
// Created by Kusidel on 19.05.2022.
//

#include "UnitHierarchy/PassengerUnit.h"
//constructor

PassengerUnit::PassengerUnit(const std::string & unitID, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer,
                             int manufacturingYear, int maxVelocity, long int mileage, int capacity)
                             : unitID(unitID), unitName(unitName), countryOfOrigin(countryOfOrigin), manufacturer(manufacturer),
                             manufacturingYear(manufacturingYear), maxVelocity(maxVelocity), mileage(mileage), capacity(capacity)
{
    archive = false;
    if (unitID.empty()) throw EmptyStringException(typeid(this).name(), quote(unitID));
    if (mileage < 0) throw NegativeNumericException(typeid(this).name(), quote(mileage));
}

PassengerUnit::~PassengerUnit() {}

//getters
const std::string & PassengerUnit::getUnitID() const {
    return unitID;
}

const std::string & PassengerUnit::getID() const {
    return getUnitID();
}

const std::string & PassengerUnit::getUnitName() const {
    return unitName;
}

const std::string & PassengerUnit::getCountryOfOrigin() const {
    return countryOfOrigin;
}

const std::string & PassengerUnit::getManufacturer() const {
    return manufacturer;
}

int PassengerUnit::getManufacturingYear() const {
    return manufacturingYear;
}

int PassengerUnit::getMaxVelocity() const {
    return maxVelocity;
}

long int PassengerUnit::getMileage() const {
    return mileage;
}

int PassengerUnit::getCapacity() const {
    return capacity;
}

bool PassengerUnit::isArchive() const {
    return archive;
}

std::string PassengerUnit::getUnitInfo() const {
    std::ostringstream ss;
    ss << "ID: " << getUnitID() << " | Name: " << getUnitName() << " | Manufacturer: " << getManufacturer() << " | Origin: " << getCountryOfOrigin() << " | Year of manufacturing: " << getManufacturingYear() << " | Vmax: " << getMaxVelocity()
        << " | Mileage: " << getMileage() << " | Capacity: " << getCapacity() << (isArchive() ? " | Archived " : " | Active");
    return ss.str();
}

std::string PassengerUnit::getInfo() const {
    return this->getUnitInfo();
}

//setters
void PassengerUnit::setMileage(long mileage) {
    if (mileage < 0) throw NegativeNumericException(typeid(this).name(), quote (mileage));
    this->mileage = mileage;
}

void PassengerUnit::setCapacity(int capacity) {
    this->capacity = capacity;
}

void PassengerUnit::setUnitName(const std::string & unitName) {
    this->unitName = unitName;
}

void PassengerUnit::setArchive(bool archive) {
    this->archive = archive;
}
