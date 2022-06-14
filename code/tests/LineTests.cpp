#include <boost/test/unit_test.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/gregorian/greg_month.hpp>
#include "Model/Line.h"
#include "UnitHierarchy/Railbus.h"

using namespace std;
namespace gt = boost::gregorian;

struct LineTestSuiteFixture {
    string id = "WAR-TOM_1230";
    double dist1 = 148.89;
    double dist2 = 51.3;
    double dist3 = 0;
    double totalDist;

    UnitPtr unit1;
    UnitPtr unit2;

    gt::date date = gt::from_undelimited_string("20220529");

    pt::ptime t1230 = pt::ptime(date) + pt::hours(12);
    pt::ptime t1232 = t1230 + pt::minutes(2);
    pt::ptime t1238 = t1230 + pt::minutes(8);
    pt::ptime t1241 = t1230 + pt::minutes(11);
    pt::ptime t1253 = t1230 + pt::minutes(23);
    pt::ptime t1258 = t1230 + pt::minutes(28);

    Node WAR = {"Warsaw", dist1, t1230, t1232};
    Node LOD = {"Boat city", dist2, t1238, t1241};
    Node TOM = {"Tomaszow Maz", dist3, t1253, t1258};
    Node ZAK = {"Zakopane", dist3, pt::not_a_date_time, pt::not_a_date_time}; //dummy node

    NodePtr node1;
    NodePtr node2;
    NodePtr node3;
    NodePtr node4;
    NodePtr node5;

    std::vector<NodePtr> route;
    std::vector<string> renovSeg;

    LineTestSuiteFixture() {
        unit1 = std::make_shared<Railbus>("DBVT98-9796", "Baureihe", "Germany", "MAN Nurnberg AG", 1961, 90, 150000, 58, "Linz am Rhein");
        unit2 = std::make_shared<Railbus>("SA105-001", "Regio Tramp", "Poland", "ZNTK Poznan", 2002, 100, 250000, 205, "Leszno");

        totalDist = dist1 + dist2 + dist3;

        node1 = std::make_shared<Node>(WAR);
        node2 = std::make_shared<Node>(LOD);
        node3 = std::make_shared<Node>(TOM);
        node4 = std::make_shared<Node>(ZAK);
        node5 = nullptr;

        route = {node1, node2, node3};
        renovSeg = {node2->name, node3->name, node4->name, ""};
    }
};

BOOST_FIXTURE_TEST_SUITE(LineTestSuite, LineTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(CtorTests) {
        Line * l = new Line(id, {node1, nullptr, node3}, unit1);
        BOOST_TEST_REQUIRE(l != nullptr);
        BOOST_TEST(l->getRoute().size() == 2);
        delete l;

        BOOST_CHECK_THROW(Line("", {node1, node2}, unit1), EmptyStringException);
        BOOST_CHECK_THROW(Line("A", {}, unit1), CollectionMismatchException);
        BOOST_CHECK_THROW(Line("A",{node1},unit1), CollectionMismatchException);
        BOOST_CHECK_THROW(Line("A", {node1, node2}, nullptr), NullPointerException);
    }

    BOOST_AUTO_TEST_CASE(GetterTests) {
        Line * l = new Line(id, route, unit1);

        BOOST_TEST(l->getID() == id);
        BOOST_TEST(l->isOpen() == true);
        BOOST_TEST(l->isRenovated() == false);
        BOOST_TEST(l->getDistance() == totalDist);
        BOOST_TEST(l->getDepartTime() == node1->departTime);
        BOOST_TEST(l->getArrivalTime() == node3->arrivalTime);
        BOOST_TEST(l->getRoute() == route);
        BOOST_TEST(l->getRenovatedSegment().empty());
        BOOST_TEST(l->getAssignedUnit() == unit1);

        string lInfo = l->getInfo();
        BOOST_TEST(lInfo.find("open") != string::npos);
        BOOST_TEST(lInfo.find("working") != string::npos);
        BOOST_TEST(lInfo.find(node1->name) != string::npos);

        delete l;
    }

    BOOST_AUTO_TEST_CASE(SetterTests) {
        Line * l = new Line(id, route, unit1);

        l->setOpen(false);
        l->setRenovated(true);
        BOOST_TEST(l->isOpen() == false);
        BOOST_TEST(l->isRenovated() == true);

        l->setRenovatedSegment(renovSeg);
        BOOST_TEST_REQUIRE(l->getRenovatedSegment().size() == 2);
        BOOST_TEST(l->getRenovatedSegment().at(0) == node2);
        BOOST_TEST(l->getRenovatedSegment().at(1) == node3);

        l->setRenovatedSegment({});
        BOOST_TEST(l->getRenovatedSegment().empty() == true);

        l->setAssignedUnit(nullptr);
        BOOST_TEST(l->getAssignedUnit() == unit1);
        l->setAssignedUnit(unit2);
        BOOST_TEST(l->getAssignedUnit() == unit2);

        delete l;
    }

    BOOST_AUTO_TEST_CASE(OtherTests) {
        Line * l = new Line(id, route, unit1);

        BOOST_TEST(l->hasNode(node1->name) == true);
        BOOST_TEST(l->hasNode(node4->name) == false);

        delete l;
    }

BOOST_AUTO_TEST_SUITE_END()