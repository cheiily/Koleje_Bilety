//
// Created by student on 01.06.2022.
//

#include "Repositories/LineReposotory.h"

LinePtr LineRepository::findByID(const std::string &id) const {
    return findById<const std::string &>(id);
}

