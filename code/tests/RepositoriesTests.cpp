#include <boost/test/unit_test.hpp>
#include "Repositories/LineReposotory.h"
#include "Repositories/TicketRepository.h"
#include "Repositories/UnitRepository.h"
#include "Model/Node.h"
#include "Model/Line.h"
#include "Model/Transit.h"
#include "TicketTypeHierarchy/Student.h"
#include "TicketTypeHierarchy/Veteran.h"
#include "Model/Ticket.h"
#include "UnitHierarchy/Railbus.h"
#include "UnitHierarchy/Tram.h"
#include "UnitHierarchy/ElectricExpress.h"

using namespace std;

struct RepositoriesTestSuiteFixture {
    LinePtr line1;
    LinePtr line2;
    LinePtr line3;
    
    TicketPtr ticket1;
    TicketPtr ticket2;
    TicketPtr ticket3;
    
    UnitPtr unit1;
    UnitPtr unit2;
    UnitPtr unit3;
    
    //Sub-parts
    NodePtr war1;
    NodePtr war2;
    NodePtr tom1;
    NodePtr tom2;
    NodePtr zak;
    NodePtr gda;

    TicketTypePtr tType1;
    TicketTypePtr tType2;

    TransitPtr transit1;
    TransitPtr transit2;
    
    string lineId1 = "War-Tom_1230";
    string lineId2 = "Tom-War_1445";
    string lineId3 = "Zak-Gda_0815";
    string transitId1 = "T_War-Tom_1230";
    string transitId2 = "T_Tom-War_1445";
    string unitId1 = "EN57-213";
    string unitId2 = "ET22-696";
    string unitId3 = "EU07-400";
    string unitName1 = "Chrobry";
    string unitName2 = "Anders";
    string unitName3 = "Pilsudski";
    string origin = "Polska";
    string manufacturer = "Pafawag Alstom";
    string city = "Boat city";
    string carrier = "PKP ICC";
    
    bool composite = true;
    
    int manufacturingYear = 1960;
    int vMax = 130;
    int capacity = 500;
    int locoQuantity = 2;
    int carQuantity = 8;
    long mileage = 21370000;
    
    double tPrice1 = 54.16;
    double tPrice2 = 21.37;
    double distance1 = 120.02;
    double distance2 = 530.15;
    double supplyVoltage = 4000.5;
    
    boost::gregorian::date gdate = boost::gregorian::from_undelimited_string("20220605");
    pt::ptime date = pt::ptime(gdate);
    pt::ptime t1230 = date + pt::hours(12) + pt::minutes(30);
    pt::ptime t1445 = date + pt::hours(14) + pt::minutes(45);
    pt::ptime t0815 = date + pt::hours(8) + pt::minutes(15);
    
    
    RepositoriesTestSuiteFixture() {
        tType1 = std::make_shared<Student>();
        tType2 = std::make_shared<Veteran>();
        
        war1 = std::make_shared<Node>(Node{"War Saw West", distance1, pt::not_a_date_time, t1230});
        tom1 = std::make_shared<Node>(Node{"Thomas City", 0, t1445, pt::not_a_date_time});
        tom2 = std::make_shared<Node>(Node{"Thomas City", distance1, pt::not_a_date_time, t1445});
        war2 = std::make_shared<Node>(Node{"War Saw West", 0, t1445 + pt::hours(2), pt::not_a_date_time});
        zak = std::make_shared<Node>(Node{"Buried", distance2, pt::not_a_date_time, t0815});
        gda = std::make_shared<Node>(Node{"Crane Scream", 0, t1445, pt::not_a_date_time});
        
        std::vector<NodePtr> vwartom = {war1, tom1};
        std::vector<NodePtr> vtomwar = {tom2, war2};
        std::vector<NodePtr> vzakgda = {zak, gda};

        unit1 = std::make_shared<Railbus>(unitId1, unitName1, origin, manufacturer, manufacturingYear, vMax, mileage, capacity, city);
        unit2 = std::make_shared<Tram>(unitId2, unitName2, origin, manufacturer, manufacturingYear, vMax, mileage, capacity, city, composite);
        unit3 = std::make_shared<ElectricExpress>(unitId3, unitName3, origin, manufacturer, manufacturingYear, vMax, mileage, capacity, carrier, locoQuantity, carQuantity, supplyVoltage);
        
        transit1 = std::make_shared<Transit>(transitId1, vwartom, unit1);
        transit2 = std::make_shared<Transit>(transitId2, vtomwar, unit2);
        
        line1 = std::make_shared<Line>(lineId1, vwartom, unit1);
        line2 = std::make_shared<Line>(lineId2, vtomwar, unit1);
        line3 = std::make_shared<Line>(lineId3, vzakgda, unit1);
        
        ticket1 = std::make_shared<Ticket>(tPrice1, tType1, transit1);
        ticket2 = std::make_shared<Ticket>(tPrice2, tType2, transit2);
        ticket3 = std::make_shared<Ticket>(tPrice2, tType1, transit1);

    }
     
};


//All repositories are instantiations of the same template class, hence basic logic tests will only be performed on a single class
BOOST_FIXTURE_TEST_SUITE(RepositoriesTestSuite, RepositoriesTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(CtorTests) {
        LineRepository * lrp = new LineRepository();
        TicketRepository * trp = new TicketRepository();
        UnitRepository * urp = new UnitRepository();
    
        BOOST_TEST_REQUIRE(trp != nullptr);
        BOOST_TEST_REQUIRE(lrp != nullptr);
        BOOST_TEST_REQUIRE(urp != nullptr);
    
        delete lrp;
        delete trp;
        delete urp;
    }

    BOOST_AUTO_TEST_CASE(AdderRemoverTests) {
        LineRepository lrp;
        
        lrp.add(nullptr);
        BOOST_TEST(lrp.size() == 0);
        lrp.add(line1);
        BOOST_TEST(lrp.get(0) == line1);
        lrp.remove(line1);
        BOOST_TEST(lrp.size() == 0);

    }
    
    
    BOOST_AUTO_TEST_CASE(GetterTests) {
        LineRepository lrp;

        lrp.add(line1);
        lrp.add(line2);
        BOOST_TEST(lrp.size() == 2);
        
        lrp.add(line3);

        BOOST_TEST(lrp.get(2) == line3);
        BOOST_TEST(lrp.get(lrp.size()) == nullptr);
        
        BOOST_TEST(lrp.report().find(line3->getInfo()) != string::npos);
        
        BOOST_TEST(lrp.size() == 3);

        BOOST_TEST(lrp.findAll() == std::vector<LinePtr>({line1, line2, line3}));
        
        BOOST_TEST(lrp.findById(lineId1) == line1);
        BOOST_TEST(lrp.findById(lineId3) == line3);
        
        double dist = distance1;
        auto f = [dist](const LinePtr & line) -> bool {
            return line->getDistance() == dist;
        };
        
        BOOST_TEST_REQUIRE(lrp.findBy(f).size() == 2);
        BOOST_TEST(lrp.findBy(f).at(0) == line1);
        BOOST_TEST(lrp.findBy(f).at(1) == line2);
        
    }

    BOOST_AUTO_TEST_CASE(UniqueTests) {
        LineRepository lrp;
        TicketRepository trp;
        UnitRepository urp;
        
        lrp.add(line1);
        lrp.add(line2);
        trp.add(ticket1);
        trp.add(ticket2);
        urp.add(unit1);
        urp.add(unit2);
        
        BOOST_TEST(lrp.findById(lineId1) == line1);
        BOOST_TEST(lrp.findById(lineId2) == line2);
        BOOST_TEST(trp.findById(ticket1->getID()) == ticket1);
        BOOST_TEST(trp.findById(ticket2->getID()) == ticket2);
        BOOST_TEST(urp.findById(unitId1) == unit1);
        BOOST_TEST(urp.findById(unitId2) == unit2);
        
    }



BOOST_AUTO_TEST_SUITE_END()