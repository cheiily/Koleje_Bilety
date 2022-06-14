#include <boost/test/unit_test.hpp>
#include "Model/Ticket.h"
#include "TicketTypeHierarchy/Student.h"
#include "TicketTypeHierarchy/Default.h"
#include "Model/Transit.h"
#include "UnitHierarchy/Railbus.h"

using namespace std;

struct TicketTestSuiteFixture {
    double price = 54.16;
    ValidationState state = ANULLED;

    TicketTypePtr type;
    TicketTypePtr type1;

    UnitPtr unit1;

    NodePtr node;
    NodePtr node2;
    TransitPtr transit;

    TicketTestSuiteFixture() {
        type = std::make_shared<Student>();
        type1 = std::make_shared<Default>();

        Node n = {"aaa", 0.0, pt::not_a_date_time, pt::not_a_date_time};
        Node n2 = {"bbb", 0.0, pt::not_a_date_time, pt::not_a_date_time};
        node = std::make_shared<Node>(n);
        node2 = std::make_shared<Node>(n2);

        unit1 = std::make_shared<Railbus>("DBVT98-9796", "Baureihe", "Germany", "MAN Nurnberg AG", 1961, 90, 150000, 58, "Linz am Rhein");

        Transit t = Transit("0", {node, node2}, unit1);
        transit = std::make_shared<Transit>(t);
    }
};

BOOST_FIXTURE_TEST_SUITE(TicketTestSuite, TicketTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(CtorTests) {
        Ticket * t = new Ticket(price, type, transit);
        BOOST_TEST_REQUIRE(t != nullptr);
        delete t;

        BOOST_CHECK_THROW(Ticket(0, nullptr, transit), NullPointerException);
        BOOST_CHECK_THROW(Ticket(0, type, nullptr), NullPointerException);
    }

    BOOST_AUTO_TEST_CASE(GetterTests) {
        Ticket * ticket = new Ticket(price, type, transit);
        pt::time_period creationDelta(ticket->getDateOfIssue(), pt::second_clock::local_time());

        BOOST_TEST(creationDelta.length().minutes() < 1);
        BOOST_TEST(ticket->getValidationState() == ValidationState::ISSUED);
        BOOST_TEST(ticket->getPrice() == price);
        BOOST_TEST(ticket->getTicketType() == type);
        BOOST_TEST(ticket->getTransit() == transit);

        string tInfo = ticket->getInfo();
        BOOST_TEST(tInfo.find(price) != string::npos);
        BOOST_TEST(tInfo.find(type->getInfo()) != string::npos);
        BOOST_TEST(tInfo.find("Issued") != string::npos);
        BOOST_TEST(tInfo.find(transit->getRoute().at(0)->name) != string::npos);

        delete ticket;
    }

    BOOST_AUTO_TEST_CASE(SetterTests) {
        Ticket * ticket = new Ticket(price, type, transit);

        BOOST_TEST(ticket->getValidationState() == ISSUED);
        ticket->setValidationState(state);
        BOOST_TEST(ticket->getValidationState() == state);

        delete ticket;
    }


BOOST_AUTO_TEST_SUITE_END()