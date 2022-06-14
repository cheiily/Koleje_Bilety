//
// Created by Kusidel on 19.05.2022.
//

#ifndef KOLEJEBILETY_URBANUNIT_H
#define KOLEJEBILETY_URBANUNIT_H
#include<iostream>
#include<string>
#include "PassengerUnit.h"

class UrbanUnit : public PassengerUnit {
private:
    std::string city;
public:
    //konstruktor i destruktor

    /**
     * Ctor initializing all fields. Utilizes <code>PassengerUnit</code>'s ctor. No additional throws.
     *
     * @throws EmptyStringException - if passed unitID is an empty string
     * @throws NegativeNumericException - if passed mileage is less than zero
     */
    UrbanUnit(const std::string & unitID, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer,
              int manufacturingYear, int maxVelocity, long int mileage, int capacity, const std::string & city);

    /**
     * Abstract dtor with empty default definition.
     */
    ~UrbanUnit() override = 0;

    //gettery
    const std::string & getCity() const;

    /**
     * Equivalent to getInfo().
     * @returns a formatted string containing info about the unit.
     */
    std::string getUnitInfo() const override;

    //settery
    void setCity(const std::string & newCity);
};
#endif //KOLEJEBILETY_URBANUNIT_H
