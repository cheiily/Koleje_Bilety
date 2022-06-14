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
#include "Managers/LineManager.h"
#include "Managers/TicketManager.h"
#include "Managers/UnitManager.h"

using namespace std;

struct ManagersTestSuiteFixture {
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
    TransitPtr transit3;

    UnitPtr unit1;
    UnitPtr unit2;

    string lineId1 = "War-Tom_1230";
    string lineId2 = "Tom-War_1445";
    string lineId3 = "Zak-Gda_0815";
    string transitId1 = "T_War-Tom_1230";
    string transitId2 = "T_Tom-War_1445";
    string transitId3 = "T_Zak-Gda_0815";
    string unitId1 = "EN57-213";
    string unitId2 = "ET22-696";
    string unitId3 = "EU07-400";
    string unitId4 = "EP09-123";
    string unitId5 = "ED72-001";
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
    int unitQuantity = 3;
    long mileage = 21370000;

    double basePrice1 = 0.15;
    double distance1 = 120.02;
    double distance2 = 530.15;
    double supplyVoltage = 4000.5;
    double engineDisplacement = supplyVoltage;

    boost::gregorian::date gdate = boost::gregorian::from_undelimited_string("20220605");
    pt::ptime date = pt::ptime(gdate);
    pt::ptime t1230 = date + pt::hours(12) + pt::minutes(30);
    pt::ptime t1445 = date + pt::hours(14) + pt::minutes(45);
    pt::ptime t0815 = date + pt::hours(8) + pt::minutes(15);


    ManagersTestSuiteFixture() {
        tType1 = std::make_shared<Student>();
        tType2 = std::make_shared<Veteran>();

        war1 = std::make_shared<Node>(Node{"War Saw West", distance1, pt::not_a_date_time, t1230});
        tom1 = std::make_shared<Node>(Node{"Thomas City", 0, t1445, pt::not_a_date_time});
        tom2 = std::make_shared<Node>(Node{"Thomas City", distance2, pt::not_a_date_time, t1445});
        war2 = std::make_shared<Node>(Node{"War Saw West", 0, t1445 + pt::hours(2), pt::not_a_date_time});
        zak = std::make_shared<Node>(Node{"Buried", distance2, pt::not_a_date_time, t0815});
        gda = std::make_shared<Node>(Node{"Crane Scream", 0, t1445, pt::not_a_date_time});

        std::vector<NodePtr> vwartom = {war1, tom1};
        std::vector<NodePtr> vtomwar = {tom2, war2};
        std::vector<NodePtr> vzakgda = {zak, gda};

        unit1 = std::make_shared<Railbus>("DBVT98-9796", "Baureihe", "Germany", "MAN Nurnberg AG", 1961, 90, 150000, 58, "Linz am Rhein");
        unit2 = std::make_shared<Railbus>("SA105-001", "Regio Tramp", "Poland", "ZNTK Poznan", 2002, 100, 250000, 205, "Leszno");

        transit1 = std::make_shared<Transit>(transitId1, vwartom, unit1);
        transit2 = std::make_shared<Transit>(transitId2, vtomwar, unit2);
        transit3 = std::make_shared<Transit>(transitId3, vzakgda, unit1);

    }

};


BOOST_FIXTURE_TEST_SUITE(ManagersTestSuite, ManagersTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(CtorTest) {
        LineManager * lm = new LineManager();
        TicketManager * tm = new TicketManager(basePrice1);
        UnitManager * um = new UnitManager();

        BOOST_TEST_REQUIRE(lm != nullptr);
        BOOST_TEST_REQUIRE(tm != nullptr);
        BOOST_TEST_REQUIRE(um != nullptr);

        delete lm;
        delete tm;
        delete um;
    }

    BOOST_AUTO_TEST_CASE(LineManagerTest) {
        LineManager lm;

        BOOST_TEST(lm.getLine(lineId1) == nullptr);

        BOOST_CHECK_THROW(lm.addNewLine("", {}, unit1), EmptyStringException);
        BOOST_CHECK_THROW(lm.addNewLine(lineId1, {}, unit1), CollectionMismatchException);
        BOOST_CHECK_THROW(lm.addNewLine(lineId1, {war1}, unit1), CollectionMismatchException);
        BOOST_CHECK_THROW(lm.addNewLine(lineId1, {war1, tom1}, nullptr), NullPointerException);
        BOOST_TEST(lm.addNewLine(lineId1, {war1, tom1}, unit1) != nullptr);
        BOOST_TEST(lm.addNewLine(lineId3, {zak, gda}, unit1) != nullptr);

        BOOST_TEST(lm.getLine(lineId1)->getID() == lineId1);
        BOOST_TEST(lm.getLine(lineId2) == nullptr);
        BOOST_TEST(lm.getLine(lineId3)->getID() == lineId3);
        BOOST_TEST(lm.findAllLines().size() == 2);

        lm.closeLine(lm.getLine(lineId1));
        BOOST_TEST(lm.findAllLines().size() == 1);

        lm.getLine(lineId1)->setOpen(true);

        lm.beginLineRenovation(lm.getLine(lineId1), {war1->name});
        BOOST_TEST(lm.getLine(lineId1)->isRenovated() == true);
        BOOST_TEST(lm.getLine(lineId1)->getRenovatedSegment().size() == 1);
        BOOST_TEST(lm.getLine(lineId1)->isOpen() == true);

        auto f = [](const LinePtr & line) -> bool {
            return (line->isRenovated() == true);
        };
        BOOST_TEST_REQUIRE(lm.findLines(f).size() == 1);
        BOOST_TEST(lm.findLines(f).at(0) == lm.getLine(lineId1));

        lm.finishLineRenovation(lm.getLine(lineId1));
        BOOST_TEST(lm.getLine(lineId1)->isRenovated() == false);
        BOOST_TEST(lm.getLine(lineId1)->getRenovatedSegment().empty() == true);

    }

    BOOST_AUTO_TEST_CASE(UnitManagerTests) {
        UnitManager um;

        BOOST_TEST(um.getUnit("") == nullptr);

        BOOST_TEST(um.registerRailBus(unitId1, unitName1, origin, manufacturer, manufacturingYear, vMax, mileage, capacity, city) != nullptr);
        BOOST_TEST(um.registerTram(unitId2, unitName2, origin, manufacturer, manufacturingYear, vMax, mileage, capacity, city, composite) != nullptr);
        BOOST_TEST(um.registerEMU(unitId3, unitName3, origin, manufacturer, manufacturingYear, vMax, mileage, capacity, carrier, unitQuantity) != nullptr);
        BOOST_TEST(um.registerElectricExpress(unitId4, "", origin, manufacturer, manufacturingYear, vMax, mileage - 1, capacity, carrier, locoQuantity, carQuantity, supplyVoltage) != nullptr);
        BOOST_TEST(um.registerDieselExpress(unitId5, "", origin, manufacturer, manufacturingYear, vMax, mileage - 1, capacity, carrier, locoQuantity, carQuantity, engineDisplacement) != nullptr);

        BOOST_CHECK_THROW(um.registerRailBus("", unitName1, origin, manufacturer, manufacturingYear, vMax, mileage, capacity, city), EmptyStringException);
        BOOST_CHECK_THROW(um.registerTram("", unitName2, origin, manufacturer, manufacturingYear, vMax, mileage, capacity, city, composite), EmptyStringException);
        BOOST_CHECK_THROW(um.registerEMU("", unitName3, origin, manufacturer, manufacturingYear, vMax, mileage, capacity, carrier, unitQuantity), EmptyStringException);
        BOOST_CHECK_THROW(um.registerElectricExpress("", "", origin, manufacturer, manufacturingYear, vMax, mileage, capacity, carrier, locoQuantity, carQuantity, supplyVoltage), EmptyStringException);
        BOOST_CHECK_THROW(um.registerDieselExpress("", "", origin, manufacturer, manufacturingYear, vMax, mileage, capacity, carrier, locoQuantity, carQuantity, engineDisplacement), EmptyStringException);
        
        BOOST_CHECK_THROW(um.registerRailBus("unique_id", unitName1, origin, manufacturer, manufacturingYear, vMax, -1, capacity, city), NegativeNumericException);
        BOOST_CHECK_THROW(um.registerTram("unique_id", unitName2, origin, manufacturer, manufacturingYear, vMax, -1, capacity, city, composite), NegativeNumericException);
        BOOST_CHECK_THROW(um.registerEMU("unique_id", unitName3, origin, manufacturer, manufacturingYear, vMax, -1, capacity, carrier, unitQuantity), NegativeNumericException);
        BOOST_CHECK_THROW(um.registerElectricExpress("unique_id", "", origin, manufacturer, manufacturingYear, vMax, -1, capacity, carrier, locoQuantity, carQuantity, supplyVoltage), NegativeNumericException);
        BOOST_CHECK_THROW(um.registerDieselExpress("unique_id", "", origin, manufacturer, manufacturingYear, vMax, -1, capacity, carrier, locoQuantity, carQuantity, engineDisplacement), NegativeNumericException);

        BOOST_CHECK_THROW(um.registerEMU("unique_id", unitName3, origin, manufacturer, manufacturingYear, vMax, -1, capacity, carrier, 0), NegativeNumericException);
        BOOST_CHECK_THROW(um.registerElectricExpress("unique_id", "", origin, manufacturer, manufacturingYear, vMax, -1, capacity, carrier, 0, carQuantity, supplyVoltage), NegativeNumericException);
        BOOST_CHECK_THROW(um.registerElectricExpress("unique_id", "", origin, manufacturer, manufacturingYear, vMax, -1, capacity, carrier, locoQuantity, 0, supplyVoltage), NegativeNumericException);
        BOOST_CHECK_THROW(um.registerElectricExpress("unique_id", "", origin, manufacturer, manufacturingYear, vMax, -1, capacity, carrier, locoQuantity, carQuantity, 0), NegativeNumericException);
        BOOST_CHECK_THROW(um.registerDieselExpress("unique_id", "", origin, manufacturer, manufacturingYear, vMax, -1, capacity, carrier, 0, carQuantity, engineDisplacement), NegativeNumericException);
        BOOST_CHECK_THROW(um.registerDieselExpress("unique_id", "", origin, manufacturer, manufacturingYear, vMax, -1, capacity, carrier, locoQuantity, 0, engineDisplacement), NegativeNumericException);
        BOOST_CHECK_THROW(um.registerDieselExpress("unique_id", "", origin, manufacturer, manufacturingYear, vMax, -1, capacity, carrier, locoQuantity, carQuantity, 0), NegativeNumericException);

        auto mil = mileage;
        auto f = [mil](const UnitPtr & unit) -> bool {
            return unit->getMileage() < mil;
        };
        BOOST_TEST_REQUIRE(um.findUnits(f).size() == 2);
        BOOST_TEST(um.findUnits(f).at(0) == um.getUnit(unitId4));
        BOOST_TEST(um.findUnits(f).at(1) == um.getUnit(unitId5));

        um.unregisterUnit(um.getUnit(unitId5));

        BOOST_TEST(um.findAllUnits().size() == 4);
        BOOST_TEST(um.findUnits(f).size() == 1);

    }

    BOOST_AUTO_TEST_CASE(TicketManagerTests) {
        TicketManager tm(basePrice1);

        id::uuid mismatch = id::random_generator()();

        BOOST_TEST(tm.getTicket(mismatch) == nullptr);

        BOOST_TEST(tm.issueTicket(tType1, transit1) != nullptr);
        BOOST_TEST(tm.issueTicket(tType2, transit2) != nullptr);
        BOOST_TEST(tm.issueTicket(tType2, transit3) != nullptr);
        BOOST_TEST(tm.issueTicket(tType1, transit3) != nullptr);
        BOOST_CHECK_THROW(tm.issueTicket(nullptr, transit1), NullPointerException);
        BOOST_CHECK_THROW(tm.issueTicket(tType1, nullptr), NullPointerException);

        BOOST_TEST_REQUIRE(tm.findAllTickets().size() == 4);

        TicketPtr issued = tm.findAllTickets().at(0);
        TicketPtr validated = tm.findAllTickets().at(1);
        TicketPtr annulled = tm.findAllTickets().at(2);
        TicketPtr returned = tm.findAllTickets().at(3);

        tm.validateTicket(validated);
        tm.annulTicket(annulled);
        tm.returnTicket(returned);

        BOOST_TEST_REQUIRE(tm.findAllTickets().size() == 2);

        tm.validateTicket(annulled);
        BOOST_TEST(annulled->getValidationState() == ANULLED);
        tm.returnTicket(annulled);
        BOOST_TEST(annulled->getValidationState() == ANULLED);
        tm.annulTicket(returned);
        BOOST_TEST(returned->getValidationState() == RETURNED);

        double pr = tm.findAllTickets().at(0)->getPrice();
        auto f = [pr](const TicketPtr & ticket) -> bool {
            return ticket->getPrice() == pr;
        };
        BOOST_TEST(tm.findTickets(f).size() == 1);

    }





BOOST_AUTO_TEST_SUITE_END()