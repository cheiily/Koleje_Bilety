//
// Created by student on 21.05.2022.
//

#ifndef KOLEJEBILETY_TICKET_H
#define KOLEJEBILETY_TICKET_H

#include <iostream>
#include <string>
#include <sstream>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "typedefs.h"
#include "TicketTypeHierarchy/TicketType.h"
#include "Model/ValidationState.h"
#include "Model/Transit.h"
#include "Exceptions.h"

namespace pt = boost::posix_time;
namespace id = boost::uuids;

class Ticket {
private:
    id::uuid ticketID;
    pt::ptime dateOfIssue;
    ValidationState validationState;
    double price;
    TransitPtr transit;
    TicketTypePtr ticketType;

public:
    //constructor
    /**
     * Basic ctor initializing all members. Clears the passed <code>route</code> set of nullptrs and checks its size. <br>
     * By default the <code>dateOfIssue</code> is set as the present moment, <code>validationState</code> as <code>ISSUED</code> and <code>ticketID</code> is a generated boost::uuids::uuid.
     *
     * @throws NullPointerException - if either <code>ticketType</code> or <code>transit</code> is a nullptr
     */
    Ticket(double price, const TicketTypePtr & ticketType, const TransitPtr & transit);

    //getters
    /**
     * Equivalent to <code>getID</code>
     */
    id::uuid getTicketID() const;

    /**
     * Equivalent to <code>getTicketID</code>
     */
    id::uuid getID() const;
    ValidationState getValidationState() const;
    pt::ptime getDateOfIssue() const;

    /**
     * @return a formatted string containing info about the ticket.
     */
    std::string getInfo() const;
    double getPrice() const;
    TicketTypePtr getTicketType() const;
    TransitPtr getTransit() const;

    //setters
    void setValidationState(ValidationState validationState);

};
#endif //KOLEJEBILETY_TICKET_H
