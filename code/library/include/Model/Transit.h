//
// Created by student on 29.05.2022.
//

#ifndef KOLEJEBILETY_TRANSIT_H
#define KOLEJEBILETY_TRANSIT_H

#include <string>
#include <vector>
#include <algorithm>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include "typedefs.h"
#include "Model/Node.h"
#include "Exceptions.h"

namespace pt = boost::posix_time;

class Transit {
private:
    std::string transitID;
    std::vector<NodePtr> route;
    UnitPtr assignedUnit;

public:
    //ctor
    /**
     * Basic ctor initializing all members. Clears the passed <code>route</code> set of nullptrs and checks its size. <br>
     * The passed route <b>must</b> have at least 2 non-null members, otherwise an exception is thrown.
     * @throws EmptyStringException - if transitId is empty
     * @throws CollectionMismatchException - if size of route after clearing is less than 2
     * @throws NullPointerException - if assignedUnit is a nullptr
     */
    Transit(const std::string & transitId, const std::vector<NodePtr> & route, const UnitPtr & assignedUnit);

    //getters
    const std::string & getID() const;
    double getDistance() const;

    /**
     * @return boost::posix_time::ptime of departing from the first station in the route
     */
    pt::ptime getDepartTime() const;

    /**
     * @return boost::posix_time::ptime of arriving to the last station in the route
     */
    pt::ptime getArrivalTime() const;
    const std::vector<NodePtr> & getRoute() const;

    /**
     * @return a formatted string containing info about the transit.
     */
    std::string getInfo() const;
    UnitPtr getAssignedUnit() const;
};


#endif //KOLEJEBILETY_TRANSIT_H
