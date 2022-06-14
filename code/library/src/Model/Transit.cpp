//
// Created by student on 29.05.2022.
//

#include "Model/Transit.h"
#include "UnitHierarchy/PassengerUnit.h"

//First assigns passed array to internal array, then clears it of nullptrs
Transit::Transit(const std::string & transitId, const std::vector<NodePtr> & route, const UnitPtr & assignedUnit) : transitID(transitId), route(route), assignedUnit(assignedUnit) {
    this->route.erase(std::remove(this->route.begin(), this->route.end(), nullptr), this->route.end());

    if (this->transitID.empty()) throw EmptyStringException(typeid(this).name(), quote(transitID));
    if (this->route.size() < 2) throw CollectionMismatchException(typeid(this).name(), quote(route));
    if (this->assignedUnit == nullptr) throw NullPointerException(typeid(this).name(), quote(assignedUnit));
}

const std::string & Transit::getID() const {
    return transitID;
}

double Transit::getDistance() const {
    double ret = 0;
    for (auto & i : route) ret += i->distanceToNextNode;
    return ret;
}

pt::ptime Transit::getDepartTime() const {
    return route.front()->departTime;
}

pt::ptime Transit::getArrivalTime() const {
    return route.back()->arrivalTime;
}

const std::vector<NodePtr> & Transit::getRoute() const {
    return route;
}

UnitPtr Transit::getAssignedUnit() const {
    return assignedUnit;
}


std::string Transit::getInfo() const {
    std::ostringstream ss;
    std::string rt;
    for (int i = 0; i < route.size() - 1; ++i)
        rt += route[i]->name + ", ";
    if (!route.empty()) rt += route[route.size()-1]->name;

    ss << "ID: " << getID() << " | Total distance: " << getDistance()
        << " | Depart time: " << getDepartTime() << " | Arrival time: " << getArrivalTime()
        << " | Route: [" << rt << ']' << " | Assigned unit: " << assignedUnit->getInfo();

    return ss.str();
}


