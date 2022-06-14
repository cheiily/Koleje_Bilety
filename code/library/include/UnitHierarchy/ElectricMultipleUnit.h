//
// Created by Kusidel on 20.05.2022.
//

#ifndef KOLEJEBILETY_ELECTRICMULTIPLEUNIT_H
#define KOLEJEBILETY_ELECTRICMULTIPLEUNIT_H
#include "IntercityUnit.h"

class ElectricMultipleUnit : public IntercityUnit {
private:
    int emuUnitQuantity;

public:
    //constructor and destructor
    /**
     * Ctor initializing all fields. Utilizes <code>IntercityUnit</code>'s ctor. <br><br>
     *
     * Additional
     * @throws NegativeNumericException - if unit quantity is lower or equal to zero.
     *
     * Base
     * @throws EmptyStringException - if passed unitID is an empty string
     * @throws NegativeNumericException - if passed mileage is less than zero
     *
     */
    ElectricMultipleUnit(const std::string & unitID, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer, int manufacturingYear, int maxVelocity, long int mileage, int capacity, const std::string & carrier, int unitQuantity);

    /**
     * Default dtor override.
     */
    ~ElectricMultipleUnit() override;

    //getters
    int getUnitQuantity() const;

    /**
     * Equivalent to getInfo().
     * @returns a formatted string containing info about the unit.
     */
    std::string getUnitInfo() const override;

    //setters
    /**
     * Sets the unit quantity.
     * @throws NegativeNumericException - if passed quantity is less than or equal to zero.
     */
    void setUnitQuantity(int unitQuantity);
};

#endif //KOLEJEBILETY_ELECTRICMULTIPLEUNIT_H
