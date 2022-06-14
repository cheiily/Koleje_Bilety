//
// Created by student on 20.05.2022.
//

#ifndef KOLEJEBILETY_ELECTRICEXPRESS_H
#define KOLEJEBILETY_ELECTRICEXPRESS_H
#include "Express.h"
class ElectricExpress : public Express {
private:
    double supplyVoltage;
public:
    //constructor and destructor
    /**
     * Ctor initializing all fields. Utilizes <code>Express</code>'s ctor. <br><br>
     *
     * Additional
     * @throws NegativeNumericException - if supply voltage is lower or equal to zero.
     *
     * Base
     * @throws EmptyStringException - if passed unitID is an empty string
     * @throws NegativeNumericException - if passed mileage is less than zero
     * @throws NegativeNumericException - if unit quantity is lower or equal to zero.
     *
     */
    ElectricExpress(const std::string & unitId, const std::string & unitName, const std::string & countryOfOrigin,
                    const std::string & manufacturer, int manufacturingYear, int maxVelocity, long mileage, int capacity,
                    const std::string & carrier, int locomotiveQuantity, int carQuantity, double supplyVoltage);

    /**
     * Default empty dtor override.
     */
    ~ElectricExpress() override;

    //getters
    double getSupplyVoltage() const;

    /**
     * Equivalent to getInfo().
     * @returns a formatted string containing info about the unit.
     */
    std::string getUnitInfo() const override;

    //setters
    /**
     * Sets the unit's supply voltage.
     * @throws NegativeNumericException - if the passed value is less than or equal to zero.
     */
    void setSupplyVoltage(double supplyVoltage);
};
#endif //KOLEJEBILETY_ELECTRICEXPRESS_H
