//
// Created by student on 01.06.2022.
//

#ifndef KOLEJEBILETY_LINEMANAGER_H
#define KOLEJEBILETY_LINEMANAGER_H

#include "Repositories/Repository.h"
#include "Repositories/LineReposotory.h"

class LineManager {
private:
    LineRepository registry;
public:

    /**
     * Searches a line by its id. Returned line can be either open or closed.
     * @param lineId - id to find the line by
     * @return std::shared_ptr<Line> if a matching Line is found. nullptr if it isn't.
     */
    LinePtr getLine(const std::string & lineId) const;

    /**
     * Searches for active Lines matching the passed predicate.
     * @param matchingMethod - std::function-assignable predicate to execute on the lines
     * @return std::vector with found elements, empty if found nothing
     */
    std::vector<LinePtr> findLines(const LinePredicate & matchingMethod) const;

    /**
     * Returns a vector with all active Lines.
     */
    std::vector<LinePtr> findAllLines() const;

    /**
     * Add a new line via its construction params.
     * @param lineId - desired Id of the Line
     * @param route - std::vector of std::shared_ptr<Node> to be set as the Line's route
     * @param assignedUnit - std::shared_ptr<PassengerUnit> to set as the Line's assigned PassengerUnit
     * @return std::shared_ptr to the newly created Line
     * @throws EmptyStringException - if lineId is empty
     * @throws EmptyCollectionException - if route is empty
     * @throws NullPointerException - if assignedUnit is nullptr
     */
    LinePtr addNewLine(const std::string & lineId, const std::vector<NodePtr> & route, const UnitPtr & assignedUnit);

    /**
     * Marks line as closed.
     * @param line - std::shared_ptr<Line>
     */
    void closeLine(const LinePtr& line);

    /**
     * The selected Line is marked renovated, however not closed (perhaps the line has a substitute transportation e.g. a bus).
     * @param line - std::shared_ptr<Line>, if there's no such active Line, nothing is changed
     * @param renovatedSegment - a vector of std::string as names of nodes to be set as the renovated segment within the Line
     * @throws CollectionMismatchException - if no nodes in renovatedSegment can be found within line's route
     */
    void beginLineRenovation(const LinePtr& line, const std::vector<std::string> & renovatedSegment);

    /**
     * Unmarks the Line as renovated, clears its renovated segment.
     * @param line - std::shared_ptr<Line> of the desired Line to be opened
     */
    void finishLineRenovation(const LinePtr& line);
};
#endif //KOLEJEBILETY_LINEMANAGER_H
