//
// Created by Kusidel on 19.05.2022.
//

#ifndef KOLEJEBILETY_PASSENGERUNIT_H
#define KOLEJEBILETY_PASSENGERUNIT_H
#include <iostream>
#include <sstream>
#include <string>
#include "Exceptions.h"

class PassengerUnit { 
private:
    std::string unitID;
    std::string unitName;
    std::string countryOfOrigin;
    std::string manufacturer;
    int manufacturingYear;
    int maxVelocity;
    long int mileage;
    int capacity;
    bool archive;

public:
    //constructor and destructor

    /**
     * Ctor initializing all fields. By default  <code>archive</code> is set to false.
     *
     * @throws EmptyStringException - if passed unitID is an empty string
     * @throws NegativeNumericException - if passed mileage is less than zero
     */
    PassengerUnit(const std::string & unitID, const std::string & unitName, const std::string & countryOfOrigin,
                  const std::string & manufacturer, int manufacturingYear, int maxVelocity, long int mileage,
                  int capacity);

    /**
     * Abstract dtor with empty default definition.
     */
    virtual ~PassengerUnit() = 0;

    //getters
    const std::string & getUnitID() const;
    const std::string & getID() const;
    const std::string & getUnitName() const;
    const std::string & getCountryOfOrigin() const;
    const std::string & getManufacturer() const;
    int getManufacturingYear() const;
    int getMaxVelocity() const;
    long int getMileage() const;
    int getCapacity() const;
    bool isArchive() const;

    /**
     * Equivalent to getInfo().
     * @returns a formatted string containing info about the unit.
     */
    virtual std::string getUnitInfo() const;

    /**
     * Equivalent to getUnitInfo().
     * @returns a formatted string containing info about the unit.
     */
    std::string getInfo() const;

    //setters

    /**
     * Sets a new mileage for the unit.
     * @throws NegativeNumericException - if passed mileage is less than 0.
     */
    void setMileage(long int mileage);
    void setCapacity(int capacity);
    void setUnitName(const std::string & unitName);
    void setArchive(bool archive);

};


#endif //KOLEJEBILETY_PASSENGERUNIT_H
