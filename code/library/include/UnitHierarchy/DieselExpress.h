//
// Created by Kusidel on 20.05.2022.
//

#ifndef KOLEJEBILETY_DIESELEXPRESS_H
#define KOLEJEBILETY_DIESELEXPRESS_H
#include "Express.h"
#include "Exceptions.h"

class DieselExpress : public Express {
    double engineDisplacement;
public:
    //constructor and destructor

    /**
     * Ctor initializing all fields. Utilizes <code>Express</code>'s ctor. <br><br>
     *
     * Additional
     * @throws NegativeNumericException - if engine displacement is lower or equal to zero.
     *
     * Base
     * @throws EmptyStringException - if passed unitID is an empty string
     * @throws NegativeNumericException - if passed mileage is less than zero
     * @throws NegativeNumericException - if unit quantity is lower or equal to zero.
     *
     */
    DieselExpress(const std::string & unitId, const std::string & unitName, const std::string & countryOfOrigin, const std::string & manufacturer,
                  int manufacturingYear, int maxVelocity, long mileage, int capacity, const std::string & carrier,
                  int locomotiveQuantity, int carQuantity, double engineDisplacement);

    /**
     * Default dtor override.
     */
    ~DieselExpress() override;

    //getters
    double getEngineDisplacement() const;

    /**
     * Equivalent to getInfo().
     * @returns a formatted string containing info about the unit.
     */
    std::string getUnitInfo() const override;

    //setters
    /**
     * Sets the unit's engine displacement.
     * @throws NegativeNumericException - if passed value is less than or equal to zero.
     */
    void setEngineDisplacement(double engineDisplacement);
};
#endif //KOLEJEBILETY_DIESELEXPRESS_H
