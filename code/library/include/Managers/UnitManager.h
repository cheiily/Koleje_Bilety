//
// Created by student on 01.06.2022.
//

#ifndef KOLEJEBILETY_UNITMANAGER_H
#define KOLEJEBILETY_UNITMANAGER_H
#include"Repositories/Repository.h"
#include"Repositories/UnitRepository.h"

using conststrref = const std::string &;

class UnitManager{
private:
    UnitRepository registry;
public:
    /**
     * Finds a unit by its id.
     * @param id - id of the desired unit.
     * @return If found - std::shared_ptr<PassengerUnit> which can be safely down-casted to the underlying object's type. <br>
     * If not found - nullptr.
     */
    UnitPtr getUnit(conststrref id) const;

    /**
     * Searches for non-archive Units matching the passed predicate within the registry.
     * @param matchingMethod std::function-assignable predicate to execute on the tickets
     * @return std::vector with found elements, empty if found nothing
     */
    std::vector<UnitPtr> findUnits(const UnitPredicate & matchingMethod) const;

    /**
     * Returns a vector with all non-archive Units.
     */
    std::vector<UnitPtr> findAllUnits() const;

    /**
     * Adds a new Railbus to the registry via the passed construction params.
     * @return std::shared_ptr<PassengerUnit> which can be then safely down-casted to the required type.
     * @throws EmptyStringException - if the unitId is empty
     * @throws NegativeNumericException - if the set mileage is less than 0
     */
    UnitPtr registerRailBus(conststrref unitId, conststrref unitName, conststrref countryOfOrigin,
                            conststrref manufacturer, int manufacturingYear, int maxVelocity, long mileage, int capacity,
                            conststrref city);

    /**
     * Adds a new Tram to the registry via the passed construction params.
     * @return std::shared_ptr<PassengerUnit> which can be then safely down-casted to the required type.
     * @throws EmptyStringException - if the unitId is empty
     * @throws NegativeNumericException - if the set mileage is less than 0
     */
    UnitPtr registerTram(conststrref unitId, conststrref unitName, conststrref countryOfOrigin,
                         conststrref manufacturer, int manufacturingYear, int maxVelocity, long mileage, int capacity,
                         conststrref city, bool composite);

    /**
     * Adds a new ElectricMultipleUnit to the registry via the passed construction params.
     * @return std::shared_ptr<PassengerUnit> which can be then safely down-casted to the required type.
     * @throws EmptyStringException - if the unitId is empty
     * @throws NegativeNumericException - if the set mileage is less than 0 or unitQuantity is less than or equal to 0
     */
    UnitPtr registerEMU(conststrref unitID, conststrref unitName, conststrref countryOfOrigin,
                        conststrref manufacturer, int manufacturingYear, int maxVelocity, long int mileage, int capacity,
                        conststrref carrier, int unitQuantity);

    /**
     * Adds a new ElectricExpress to the registry via the passed construction params.
     * @return std::shared_ptr<PassengerUnit> which can be then safely down-casted to the required type.
     * @throws EmptyStringException - if the unitId is empty
     * @throws NegativeNumericException - if the set mileage is less than 0 or any of the set of
     * locomotiveQuantity, carQuantity, supplyVoltage is less than or equal to 0
     */
    UnitPtr registerElectricExpress(conststrref unitId, conststrref unitName, conststrref countryOfOrigin,
                                    conststrref manufacturer, int manufacturingYear, int maxVelocity, long mileage, int capacity,
                                    conststrref carrier, int locomotiveQuantity, int carQuantity, double supplyVoltage);

    /**
     * Adds a new DieselExpress to the registry via the passed construction params.
     * @return std::shared_ptr<PassengerUnit> which can be then safely down-casted to the required type.
     * @throws EmptyStringException - if the unitId is empty
     * @throws NegativeNumericException - if the set mileage is less than 0 or any of the set of
     * locomotiveQuantity, carQuantity, engineDisplacement is less than or equal to 0
     */
    UnitPtr registerDieselExpress(conststrref unitId, conststrref unitName, conststrref countryOfOrigin, conststrref manufacturer,
                                  int manufacturingYear, int maxVelocity, long mileage, int capacity,
                                  conststrref carrier, int locomotiveQuantity, int carQuantity, double engineDisplacement);

    /**
     * Archives the unit.
     * @param unit - std::shared_ptr<PassengerUnit> of the archived unit. If passed nullptr, nothing will change.
     */
    void unregisterUnit(const UnitPtr &unit);


};
#endif //KOLEJEBILETY_UNITMANAGER_H
