//
// Created by Kusidel on 20.05.2022.
//

#ifndef KOLEJEBILETY_EXPRESS_H
#define KOLEJEBILETY_EXPRESS_H
#include "IntercityUnit.h"

class Express : public IntercityUnit {
private:
    int locomotiveQuantity;
    int carQuantity;

public:
    /**
     * Ctor initializing all fields. Utilizes <code>IntercityUnit</code>'s ctor. <br><br>
     *
     * Additional
     * @throws NegativeNumericException - if either car or locomotive quantity is lower or equal to zero.
     *
     * Base
     * @throws EmptyStringException - if passed unitID is an empty string
     * @throws NegativeNumericException - if passed mileage is less than zero
     *
     */
    Express(const std::string & unitID, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer,
            int manufacturingYear, int maxVelocity, long int mileage, int capacity, const std::string & carrier, int locomotiveQuantity, int carQuantity);

    /**
     * Abstract dtor with empty default definition.
     */
    ~Express() override = 0;

    //getters
    int getLocomotiveQuantity() const;
    int getCarQuantity() const;

    /**
     * Equivalent to getInfo().
     * @returns a formatted string containing info about the unit.
     */
    std::string getUnitInfo() const override;

    //setters
    /**
     * Sets the unit's locomotive quantity.
     * @throws NegativeNumericException if passed quantity is less than or equal to zero.
     */
    void setLocomotiveQuantity(int locomotiveQuantity);

    /**
     * Sets the unit's car quantity.
     * @throws NegativeNumericException if passed quantity is less than or equal to zero.
     */
    void setCarQuantity(int carQuantity);
};


#endif //KOLEJEBILETY_EXPRESS_H
