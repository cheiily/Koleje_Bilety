//
// Created by student on 22.05.2022.
//

#include "Model/Ticket.h"

Ticket::Ticket(double price, const TicketTypePtr & ticketType, const TransitPtr & transit)
    : price(price), ticketType(ticketType), transit(transit) {
    dateOfIssue = pt::second_clock::local_time();
    validationState = ISSUED;
    ticketID = id::random_generator()();

    if (ticketType == nullptr) throw NullPointerException(typeid(this).name(), quote(ticketType));
    if (transit == nullptr) throw NullPointerException(typeid(this).name(), quote(transit));
}


id::uuid Ticket::getTicketID() const {
    return ticketID;
}

id::uuid Ticket::getID() const {
    return getTicketID();
}

ValidationState Ticket::getValidationState() const {
    return validationState;
}

double Ticket::getPrice() const {
    return price;
}

pt::ptime Ticket::getDateOfIssue() const {
    return dateOfIssue;
}

std::string Ticket::getInfo() const {
    std::ostringstream ss;
    ss << "ID: " << getTicketID() << " | Price: " << getPrice() << " | Date of issue: " << getDateOfIssue() << " | State: ";
    switch (getValidationState()) {
        case ISSUED:
            ss << "Issued";
            break;
        case VALIDATED:
            ss << "Validated";
            break;
        case RETURNED:
            ss << "Returned";
            break;
        case ANULLED:
            ss << "Anulled";
            break;
    }
    ss << " | " << ticketType->getInfo() << " | Transit: " << transit->getInfo();
    return ss.str();
}


void Ticket::setValidationState(ValidationState validationState) {
    this->validationState = validationState;
}

TicketTypePtr Ticket::getTicketType() const {
    return ticketType;
}

TransitPtr Ticket::getTransit() const {
    return transit;
}