//
// Created by student on 01.06.2022.
//

#ifndef KOLEJEBILETY_LINEREPOSOTORY_H
#define KOLEJEBILETY_LINEREPOSOTORY_H
#include "Model/Line.h"
#include "Repository.h"

class LineRepository : public Repository<Line> {

    /**
     * Implementation of the base-class function with template type specified as std::string.
     * @param id - element id
     * @return std::shared_ptr of the found element or nullptr if found nothing
     */
    LinePtr findByID(const std::string &id) const;
};

#endif //KOLEJEBILETY_LINEREPOSOTORY_H
