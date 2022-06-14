//
// Created by student on 01.06.2022.
//
#include "typedefs.h"
#include "Repositories/UnitRepository.h"

UnitPtr UnitRepository::findByID(const std::string &id) const {
    return findById<const std::string &>(id);
}