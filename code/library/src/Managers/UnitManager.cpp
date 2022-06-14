//
// Created by student on 01.06.2022.
//

#include "Managers/UnitManager.h"
#include "UnitHierarchy/Railbus.h"
#include "UnitHierarchy/Tram.h"
#include "UnitHierarchy/ElectricMultipleUnit.h"
#include "UnitHierarchy/ElectricExpress.h"
#include "UnitHierarchy/DieselExpress.h"

using conststrref = const std::string &;

UnitPtr UnitManager::getUnit(conststrref id) const {
    return registry.findById(id);
}

std::vector<UnitPtr> UnitManager::findUnits(const UnitPredicate & matchingMethod) const {
    auto f = [matchingMethod](const UnitPtr & unit) -> bool {
        return (matchingMethod(unit) && unit->isArchive() == false);
    };
    return registry.findBy(f);
}

std::vector<UnitPtr> UnitManager::findAllUnits() const {
    return findUnits([](const UnitPtr & unit) { return true; });
}

UnitPtr
UnitManager::registerRailBus(conststrref unitId, conststrref unitName, conststrref countryOfOrigin,
                             conststrref manufacturer, int manufacturingYear, int maxVelocity, long mileage,
                             int capacity, conststrref city) {
    UnitPtr ptr = getUnit(unitId);
    if(ptr!= nullptr) return ptr;

    ptr = std::make_shared<Railbus>(unitId,unitName, countryOfOrigin,manufacturer,manufacturingYear,maxVelocity,mileage,capacity,city);
    registry.add(ptr);
    return ptr;
}

UnitPtr
UnitManager::registerTram(conststrref unitId, conststrref unitName, conststrref countryOfOrigin,
                          conststrref manufacturer, int manufacturingYear, int maxVelocity, long mileage,
                          int capacity, conststrref city, bool composite) {
    UnitPtr ptr = getUnit(unitId);
    if(ptr!=nullptr) return ptr;

    ptr = std::make_shared<Tram>(unitId,unitName,countryOfOrigin,manufacturer,manufacturingYear,maxVelocity,mileage,capacity,city,composite);
    registry.add(ptr);
    return ptr;
}

UnitPtr UnitManager::registerElectricExpress(conststrref unitId, conststrref unitName,
                                             conststrref countryOfOrigin, conststrref manufacturer,
                                             int manufacturingYear, int maxVelocity, long mileage, int capacity,
                                             conststrref carrier, int locomotiveQuantity, int carQuantity,
                                             double supplyVoltage) {
    UnitPtr ptr = getUnit(unitId);
    if(ptr!=nullptr) return ptr;

    ptr = std::make_shared<ElectricExpress>(unitId,unitName,countryOfOrigin,manufacturer,manufacturingYear,maxVelocity,mileage,capacity,carrier,locomotiveQuantity,carQuantity,supplyVoltage);
    registry.add(ptr);
    return ptr;
}

UnitPtr UnitManager::registerDieselExpress(conststrref unitId, conststrref unitName,
                                           conststrref countryOfOrigin, conststrref manufacturer,
                                           int manufacturingYear, int maxVelocity, long mileage, int capacity,
                                           conststrref carrier, int locomotiveQuantity, int carQuantity,
                                           double engineDisplacement) {
    UnitPtr ptr = getUnit(unitId);
    if(ptr!=nullptr) return ptr;

    ptr = std::make_shared<DieselExpress>(unitId,unitName,countryOfOrigin,manufacturer,manufacturingYear,maxVelocity,mileage,capacity,carrier,locomotiveQuantity,carQuantity,engineDisplacement);
    registry.add(ptr);
    return ptr;
}

UnitPtr UnitManager::registerEMU(conststrref unitID, conststrref unitName, conststrref countryOfOrigin,
                         conststrref manufacturer, int manufacturingYear, int maxVelocity, long mileage,
                         int capacity, conststrref carrier, int unitQuantity) {
    UnitPtr ptr = getUnit(unitID);
    if(ptr!=nullptr) return ptr;

    ptr = std::make_shared<ElectricMultipleUnit>(unitID,unitName,countryOfOrigin,manufacturer,manufacturingYear,maxVelocity,mileage,capacity,carrier,unitQuantity);
    registry.add(ptr);
    return ptr;
}

void UnitManager::unregisterUnit(const UnitPtr &unit) {
    UnitPtr found = getUnit(unit->getUnitID());
    if(found!=nullptr){
        unit->setArchive(true);
    }
}
