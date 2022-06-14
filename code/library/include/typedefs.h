//
// Created by Kusidel on 19.05.2022.
//

#ifndef KOLEJEBILETY_TYPEDEFS_H
#define KOLEJEBILETY_TYPEDEFS_H
#include <memory>
#include <functional>
class PassengerUnit;
class Ticket;
class TicketType;
class Node;
class Line;
class Transit;


template <class T>
using Ptr = std::shared_ptr<T>;
//template <class T>
//using UPtr = std::unique_ptr<T>;
template <class PT>
using Predicate = std::function<bool(PT)>;


typedef Ptr<PassengerUnit> UnitPtr;
typedef Ptr<Ticket> TicketPtr;
typedef Ptr<TicketType> TicketTypePtr;
typedef Ptr<Node> NodePtr;                  //Perhaps this would be better as a unique pointer
typedef Ptr<Line> LinePtr;
typedef Ptr<Transit> TransitPtr;


typedef Predicate<UnitPtr> UnitPredicate;
typedef Predicate<LinePtr> LinePredicate;
typedef Predicate<TicketPtr> TicketPredicate;


#endif //KOLEJEBILETY_TYPEDEFS_H
