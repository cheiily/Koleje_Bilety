//
// Created by student on 22.05.2022.
//

#include <string>
#include "TicketTypeHierarchy/Other.h"

int Other::getDiscount() const {
    return 10;
}

std::string Other::getType() const {
    return "Other";
}
