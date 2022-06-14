//
// Created by student on 01.06.2022.
//

#ifndef KOLEJEBILETY_UNITREPOSITORY_H
#define KOLEJEBILETY_UNITREPOSITORY_H
#include"UnitHierarchy/PassengerUnit.h"
#include"Repository.h"

class UnitRepository : public Repository<PassengerUnit> {

    /**
     * Implementation of the base-class function with template type specified as std::string.
     * @param id - element id
     * @return std::shared_ptr of the found element or nullptr if found nothing
     */
    UnitPtr findByID(const std::string & id) const;
};



#endif //KOLEJEBILETY_UNITREPOSITORY_H
