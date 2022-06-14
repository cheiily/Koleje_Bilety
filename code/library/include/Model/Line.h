//
// Created by student on 28.05.2022.
//

#ifndef KOLEJEBILETY_LINE_H
#define KOLEJEBILETY_LINE_H

#include <string>
#include <vector>
#include <algorithm>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include "typedefs.h"
#include "Model/Node.h"
#include "Exceptions.h"

namespace pt = boost::posix_time;


class Line {
private:
    std::string lineID;
    bool open;
    bool renovated;
    std::vector<NodePtr> route;
    std::vector<NodePtr> renovatedSegment;
    UnitPtr assignedUnit;

public:
    //ctor
    /**
     * Basic ctor initializing all members. Clears the passed <code>route</code> set of nullptrs and checks its size. <br>
     * The passed route <b>must</b> have at least 2 non-null members, otherwise an exception is thrown. <br>
     * By default <code>open</code> is set to true and <code>renovated</code> to false.
     *
     * @throws EmptyStringException - if lineId is empty
     * @throws CollectionMismatchException - if size of route after clearing is less than 2
     * @throws NullPointerException - if assignedUnit is a nullptr
     */
    Line(const std::string & lineId, const std::vector<NodePtr> & route, UnitPtr unit);

    //getters
    const std::string & getID() const;
    bool isOpen() const;
    bool isRenovated() const;
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
    const std::vector<NodePtr> & getRenovatedSegment() const;
    UnitPtr getAssignedUnit() const;

    /**
     * @return a formatted string containing info about the line.
     */
    std::string getInfo() const;

    //setters
    void setOpen(bool open);
    void setRenovated(bool renovated);

    /**
     * Sets the assigned unit.
     * If the passed arg is a nullptr, nothing is changed.
     */
    void setAssignedUnit(UnitPtr assignedUnit);

    /**
     * Sets the renovated segment variable.
     * If the passed set is empty, the internal renovated segment set is cleared.
     * Otherwise, out of the passed set, only nodes that are already present in the line's route and are not null are appended to the renovated segment set.
     * If the passed set is not empty but only contains nullptr's the internal renovated segment set is not changed.
     * Make sure to clear the segment every time a renovation is finished, otherwise it may retain unwanted nodes.
     * @param renovatedSegment - vector of nodes' names in std::strings
     */
    void setRenovatedSegment(std::vector<std::string> renovatedSegment);

    //other
    /**
     * Checks whether the line contains a node with the specified name.
     */
    bool hasNode(const std::string & nodeName) const;
};


#endif //KOLEJEBILETY_LINE_H
