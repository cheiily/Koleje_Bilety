//
// Created by student on 22.05.2022.
//

#ifndef KOLEJEBILETY_VETERAN_H
#define KOLEJEBILETY_VETERAN_H

#include "TicketType.h"

class Veteran : public TicketType {
public:
    /**
     * @return integer which refers to amount of percentage discount
     */
    int getDiscount() const override;

    /**
     * @return string containing name of type
     */
    std::string getType() const override;
};
#endif //KOLEJEBILETY_VETERAN_H
