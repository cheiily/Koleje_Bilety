//
// Created by student on 22.05.2022.
//
#include "TicketTypeHierarchy/TicketType.h"

std::string TicketType::getTypeInfo() const {
    return "Ticket type: " + getType() +" - " +std::to_string(getDiscount())+"% discount";
}

std::string TicketType::getInfo() const {
    return this->getTypeInfo();
}

double TicketType::applyDiscount(double price) const {
    return price * ((100 - getDiscount()) / 100.0);
}



