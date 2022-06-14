//
// Created by student on 28.05.2022.
//

#ifndef KOLEJEBILETY_NODE_H
#define KOLEJEBILETY_NODE_H

#include <string>
#include <boost/date_time/posix_time/ptime.hpp>

/**
 * A structure uniquely representing a node/station and its relations to other nodes within a single line.
 * Multiple lines can and should have different objects referring to the same physical station.
 * In order to simplify interaction with such nodes it is advised that the <code>name</code>
 *  variable should be set to the represented physical station's name or something similarly representative, rather than a unique identifier.
 */
struct Node {
    const std::string name;
    const double distanceToNextNode;
    const boost::posix_time::ptime arrivalTime;
    const boost::posix_time::ptime departTime;
};

#endif //KOLEJEBILETY_NODE_H
