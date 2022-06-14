#include "Managers/TicketManager.h"



TicketManager::TicketManager(double basePrice) : basePrice(basePrice) {}

double TicketManager::calculateFinalPrice(TransitPtr transit, TicketTypePtr discount) const {
    return discount->applyDiscount(basePrice * transit->getDistance());
}

void TicketManager::setBasePrice(double price) {
    this->basePrice = price;
}

double TicketManager::getBasePrice() const {
    return basePrice;
}

TicketPtr TicketManager::getTicket(const id::uuid &id) const {
    return registry.findById(id);
}

std::vector<TicketPtr> TicketManager::findTickets(const TicketPredicate & matchingMethod) const {
    auto f = [matchingMethod](const TicketPtr & ticket) -> bool {
        return matchingMethod(ticket) && (ticket->getValidationState() == ISSUED || ticket->getValidationState() == VALIDATED);
    };
    return registry.findBy(f);
}

std::vector<TicketPtr> TicketManager::findAllTickets() const {
    return findTickets([](const TicketPtr & ticket) { return true; });
}

TicketPtr TicketManager::issueTicket(const TicketTypePtr & type, const TransitPtr & transit) {
    if (type == nullptr) throw NullPointerException(typeid(this).name(), std::string(quote(issueTicket)) + " - " + quote(ticketType));
    if (transit == nullptr) throw NullPointerException(typeid(this).name(), std::string(quote(issueTicket)) + " - " + quote(transit));

    double price = calculateFinalPrice(transit, type);

    TicketPtr ptr = std::make_shared<Ticket>(price, type, transit);
    registry.add(ptr);
    return ptr;
}

void TicketManager::validateTicket(const TicketPtr &ticket) {
    TicketPtr found = getTicket(ticket->getTicketID());
    if(found!= nullptr) {
        if (found->getValidationState() != ISSUED) return;
        found->setValidationState(VALIDATED);
    }
}

void TicketManager::returnTicket(const TicketPtr &ticket) {
    TicketPtr found = getTicket(ticket->getTicketID());
    if(found!= nullptr) {
        if (found->getValidationState() != ISSUED && found->getValidationState() != VALIDATED) return;
        found->setValidationState(RETURNED);
    }
}

void TicketManager::annulTicket(const TicketPtr &ticket) {
    TicketPtr found = getTicket(ticket->getTicketID());
    if(found!= nullptr) {
        if (found->getValidationState() != ISSUED && found->getValidationState() != VALIDATED) return;
        found->setValidationState(ANULLED);
    }
}


