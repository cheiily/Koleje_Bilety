//
// Created by student on 22.05.2022.
//

#ifndef KOLEJEBILETY_STUDENT_H
#define KOLEJEBILETY_STUDENT_H

#include "TicketType.h"

class Student : public TicketType {
public:
    /**
     *
     * @return integer which refers to amount of percentage discount
     */
    int getDiscount() const override;
    /**
     * @return string containing name of type
     */
    std::string getType() const override;
};
#endif //KOLEJEBILETY_STUDENT_H
