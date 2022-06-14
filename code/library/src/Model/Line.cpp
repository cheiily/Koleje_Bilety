//
// Created by student on 28.05.2022.
//

#include "Model/Line.h"
#include "UnitHierarchy/PassengerUnit.h"

Line::Line(const std::string & lineId, const std::vector<NodePtr> & route, UnitPtr assignedUnit) : lineID(lineId), route(route), assignedUnit(assignedUnit) {
    open = true;
    renovated = false;

    this->route.erase(std::remove(this->route.begin(), this->route.end(), nullptr), this->route.end());

    if (this->lineID.empty()) throw EmptyStringException(typeid(this).name(), quote(lineID));
    if (this->route.size() < 2) throw CollectionMismatchException(typeid(this).name(),quote(route));
    if (this->assignedUnit == nullptr) throw NullPointerException(typeid(this).name(), quote(assignedUnit));
}


const std::string & Line::getID() const {
    return lineID;
}

bool Line::isOpen() const {
    return open;
}

bool Line::isRenovated() const {
    return renovated;
}

double Line::getDistance() const {
    double ret = 0;
    for (auto & i : route) ret += i->distanceToNextNode;
    return ret;
}

pt::ptime Line::getDepartTime() const {
    return route.empty() ? pt::not_a_date_time : route.front()->departTime;
}

pt::ptime Line::getArrivalTime() const {
    return route.empty() ? pt::not_a_date_time : route.back()->arrivalTime;
}

const std::vector<NodePtr> & Line::getRoute() const {
    return route;
}

const std::vector<NodePtr> & Line::getRenovatedSegment() const {
    return renovatedSegment;
}

UnitPtr Line::getAssignedUnit() const {
    return assignedUnit;
}

std::string Line::getInfo() const {
    std::ostringstream ss;
    std::string rt;
    for (auto & i : route)
        rt += i->name + ", ";
    rt = rt.substr(0, rt.length() - 2);
    std::string rn;
    for (auto & i : renovatedSegment)
        rn += i->name + ", ";
    rn = rn.substr(0, rn.length() - 2);


    ss << "ID: " << getID() << " | "
        << (isOpen() ? "open" : "closed") << " | " << (isRenovated() ? "renovated" : "working")
        << " | Total distance: " << getDistance()
        << " | Depart time:" << getDepartTime() << " | Arrival time: " << getArrivalTime()
        << " | Route: [" << rt << "] | Renovated segment: [" << rn << "]"
        << " | Assigned Unit: " << assignedUnit->getInfo();

    return ss.str();
}

void Line::setOpen(bool open) {
    this->open = open;
}

void Line::setRenovated(bool renovated) {
    this->renovated = renovated;
}

void Line::setAssignedUnit(UnitPtr assignedUnit) {
    if (assignedUnit == nullptr) return;

    this->assignedUnit = assignedUnit;
}

void Line::setRenovatedSegment(std::vector<std::string> renovatedSegment) {
    if (renovatedSegment.empty()) {
        this->renovatedSegment.clear();
        return;
    }

    //Only add nodes which can be found within the route
    for (auto & passed : renovatedSegment) {
        for (auto & internal : route) {
            if (internal->name == passed) {
                this->renovatedSegment.push_back(internal);
                continue;
            }
        }
    }
}

bool Line::hasNode(const std::string & nodeName) const {
    for (auto & i : route)
        if (i->name == nodeName) return true;
    return false;
}
