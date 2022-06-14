//
// Created by student on 01.06.2022.
//

#include "typedefs.h"
#include "Repositories/TicketRepository.h"

TicketPtr TicketRepository::findByID(const boost::uuids::uuid & id) const {
    return findById<const boost::uuids::uuid &>(id);
}