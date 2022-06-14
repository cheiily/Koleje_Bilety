//
// Created by student on 01.06.2022.
//

#ifndef KOLEJEBILETY_TICKETREPOSITORY_H
#define KOLEJEBILETY_TICKETREPOSITORY_H

#include "Model/Ticket.h"
#include "Repository.h"
class TicketRepository : public Repository<Ticket> {

    /**
     * Implementation of the base-class function with template type specified as boost::uuids::uuid.
     * @param id - element id
     * @return std::shared_ptr of the found element or nullptr if found nothing
     */
    TicketPtr findByID(const boost::uuids::uuid & id) const;
};
#endif //KOLEJEBILETY_TICKETREPOSITORY_H
