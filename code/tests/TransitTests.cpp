#include <boost/test/unit_test.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/gregorian/greg_month.hpp>
#include "Model/Transit.h"
#include "UnitHierarchy/Railbus.h"

using namespace std;
namespace gt = boost::gregorian;

struct TransitTestSuiteFixture {
    string id = "T_WAR-TOM_1230";
    double dist1 = 148.89;
    double dist2 = 51.3;
    double dist3 = 0;
    double totalDist;

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

    NodePtr node1;
    NodePtr node2;
    NodePtr node3;

    UnitPtr unit1;

    std::vector<NodePtr> route;
    std::vector<NodePtr> renovSeg;

    TransitTestSuiteFixture() {
        totalDist = dist1 + dist2 + dist3;

        node1 = std::make_shared<Node>(WAR);
        node2 = std::make_shared<Node>(LOD);
        node3 = std::make_shared<Node>(TOM);

        route = {node1, node2, node3};
        renovSeg = {node2, node3};

        unit1 = std::make_shared<Railbus>("DBVT98-9796", "Baureihe", "Germany", "MAN Nurnberg AG", 1961, 90, 150000, 58, "Linz am Rhein");
    }
};


BOOST_FIXTURE_TEST_SUITE(TransitTestSuite, TransitTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(CtorTests) {
        Transit * t = new Transit(id, {node1, node2, nullptr}, unit1);
        BOOST_TEST_REQUIRE(t != nullptr);
        BOOST_TEST(t->getRoute().size() == 2);
        delete t;

        BOOST_CHECK_THROW(Transit("", {node1, node2}, unit1), EmptyStringException);
        BOOST_CHECK_THROW(Transit("A", {}, unit1), CollectionMismatchException);
        BOOST_CHECK_THROW(Transit("A",{node1},unit1), CollectionMismatchException);
        BOOST_CHECK_THROW(Transit("A", {node1, node2}, nullptr), NullPointerException);
    }

    BOOST_AUTO_TEST_CASE(GetterTests) {
        Transit * t = new Transit(id, route, unit1);

        BOOST_TEST(t->getID() == id);
        BOOST_TEST(t->getDistance() == totalDist);
        BOOST_TEST(t->getDepartTime() == node1->departTime);
        BOOST_TEST(t->getArrivalTime() == node3->arrivalTime);
        BOOST_TEST(t->getRoute() == route);
        BOOST_TEST(t->getAssignedUnit() == unit1);

        string tInfo = t->getInfo();

        BOOST_TEST(tInfo.find(id) != string::npos);
        BOOST_TEST(tInfo.find(node3->name) != string::npos);
        BOOST_TEST(tInfo.find(unit1->getID()) != string::npos);

        delete t;
    }

BOOST_AUTO_TEST_SUITE_END()