//
// Created by student on 21.05.2022.
//

#ifndef KOLEJEBILETY_TICKETTYPE_H
#define KOLEJEBILETY_TICKETTYPE_H

#include <iostream>

/**
 * Base abstract ticket type class.
 */
class TicketType {
public:

    /**
     * To-be-overridden abstract method returning @returns the discount value in percents.
     */
    virtual int getDiscount() const = 0;

    /**
     * To-be-overridden abstract method returning @returns the name of the discount type in string form.
     */
    virtual std::string getType() const = 0;

    /**
     * Employes <code>getDiscount</code> and <code>getType</code> <br>
     * Equivalent to <code>getInfo</code>
     * @returns formatted info including name of the ticket type and discount percentage.
     */
    virtual std::string getTypeInfo() const;

    /**
     * Employes <code>getDiscount</code> and <code>getType</code> <br>
     * Equivalent to <code>getTypeInfo</code>
     * @returns formatted info including name of the ticket type and discount percentage.
     */
    virtual std::string getInfo() const;

    /**
     * Employes <code>getDiscount</code> to get the percentage.
     * @returns a value after applying discount.
     */
    virtual double applyDiscount(double price) const;
};
#endif //KOLEJEBILETY_TICKETTYPE_H
