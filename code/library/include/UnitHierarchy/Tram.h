//
// Created by student on 20.05.2022.
//

#ifndef KOLEJEBILETY_TRAM_H
#define KOLEJEBILETY_TRAM_H

#include "UrbanUnit.h"

class Tram : public UrbanUnit {
private:
    bool composite;

public:

    /**
     * Ctor initializing all fields. Utilizes <code>UrbanUnit</code>'s ctor. No additional throws.
     *
     * @throws EmptyStringException - if passed unitID is an empty string
     * @throws NegativeNumericException - if passed mileage is less than zero
     */
    Tram(const std::string & unitId, const std::string & unitName, const std::string & countryOfOrigin,
         const std::string & manufacturer, int manufacturingYear, int maxVelocity, long mileage, int capacity,
         const std::string & city, bool composite);

    /**
     * Default dtor override.
     */
    ~Tram() override = default;


    bool isComposite() const;

    void setComposite(bool composite);

    /**
     * Equivalent to getInfo().
     * @returns a formatted string containing info about the unit.
     */
    std::string getUnitInfo() const override;
};


#endif //KOLEJEBILETY_TRAM_H
