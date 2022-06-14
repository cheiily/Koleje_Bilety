//
// Created by student on 01.06.2022.
//

#ifndef KOLEJEBILETY_TICKETMANAGER_H
#define KOLEJEBILETY_TICKETMANAGER_H
#include "Repositories/Repository.h"
#include "Repositories/TicketRepository.h"

namespace id = boost::uuids;

/**
 * @note
 * A "valid ticket" means the ticket's validation state is either ISSUED or VALIDATED.
 * Likewise, the "valid set" is a subset of all contained tickets that are "valid".
 */
class TicketManager{
private:
    double basePrice;
    TicketRepository registry;

    /**
     * Calculates a to-be-generated Ticket's price using the passed TicketType's discount, Transit's distance and this TicketManager's basePrice.
     * @warning Trying to pass a null pointer to either of the arguments causes undefined behavior.
     * @param transit
     * @param discount
     * @return
     */
    double calculateFinalPrice(TransitPtr transit, TicketTypePtr discount) const;
public:
    TicketManager(double basePrice);

    void setBasePrice(double price);
    double getBasePrice() const;

    /**
     * Retrieves a ticket from the valid set.
     * @param id - uuid of the desired ticket
     * @return std::shared_ptr if found, nullptr if not.
     */
    TicketPtr getTicket(const id::uuid & id) const;

    /**
     * Searches for Tickets matching the passed predicate within the valid tickets set.
     * @param matchingMethod - std::function-assignable predicate to execute on the tickets
     * @return std::vector with found elements, empty if found nothing
     */
    std::vector<TicketPtr> findTickets(const TicketPredicate & matchingMethod) const;

    /**
     * Returns a vector with all valid Tickets.
     */
    std::vector<TicketPtr> findAllTickets() const;

    /**
     * Creates a new Ticket with params provided and returns an std::shared_ptr of it.
     * The price is calculated utilizing the passed TicketType's discount, Transit's distance and this TicketManager's basePrice;
     * @note A new ticket is not automatically validated, however it is a "valid" ticket until checked by the controller and hence will be placed in the valid set.
     * @param type - std::shared_ptr<TicketType> declared type of the ticket
     * @param transit - std::shared_ptr<Transit> declared transit to set to the ticket
     * @throws NullPointerException - if either type or transit is empty
     */
    TicketPtr issueTicket(const TicketTypePtr & type, const TransitPtr & transit);

    /**
     * Marks ticket as validated. Can only validate ticket in ISSUED state. <br>
     * If passed arg is a nullptr, nothing is changed.
     * @param ticket - std::shared_ptr of desired ticket
     */
    void validateTicket(const TicketPtr& ticket);

    /**
     * Marks ticket as returned. Irreversible. <br>
     * If the passed arg is a nullptr or cannot be found in the valid set, nothing is changed.
     * @param ticket - std::shared_ptr of desired ticket
     */
    void returnTicket(const TicketPtr& ticket);

    /**
     * Marks ticket as annulled. Irreversible. <br>
     * If the passed arg is a nullptr or cannot be found in the valid set, nothing is changed.
     * @param ticket - std::shared_ptr of desired ticket
     */
    void annulTicket(const TicketPtr& ticket);
};


#endif //KOLEJEBILETY_TICKETMANAGER_H
