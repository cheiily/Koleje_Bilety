//
// Created by Kusidel on 19.05.2022.
//

#ifndef KOLEJEBILETY_INTERCITYUNIT_H
#define KOLEJEBILETY_INTERCITYUNIT_H
#include <iostream>
#include <string>
#include "PassengerUnit.h"

class IntercityUnit : public PassengerUnit {
private:
    std::string carrier;         //przewoznik

public:
    //constructor, destructor

    /**
     * Ctor initializing all fields. Utilizes <code>PassengerUnit</code>'s ctor. No additional throws.
     *
     * @throws EmptyStringException - if passed unitID is an empty string
     * @throws NegativeNumericException - if passed mileage is less than zero
     */
    IntercityUnit(const std::string & unitID, const std::string & unitName, const std::string & countryOfOrigin,
                  const std::string & manufacturer, int manufacturingYear, int maxVelocity, long int mileage, int capacity,
                  const std::string & carrier);

    /**
     * Abstract dtor with default definition.
     */
    ~IntercityUnit() override = 0;

    //getters
    const std::string & getCarrier() const;

    /**
     * Equivalent to getInfo().
     * @returns a formatted string containing info about the unit.
     */
    std::string getUnitInfo() const override;

    void setCarrier(const std::string & carrier);
};
#endif //KOLEJEBILETY_INTERCITYUNIT_H
