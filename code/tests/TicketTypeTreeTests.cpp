#include <boost/test/unit_test.hpp>
#include "TicketTypeHierarchy/Child.h"
#include "TicketTypeHierarchy/Default.h"
#include "TicketTypeHierarchy/Other.h"
#include "TicketTypeHierarchy/Student.h"
#include "TicketTypeHierarchy/Veteran.h"

using namespace std;

struct TicketTypeTestSuiteFixture{
    double testPrice = 100.0;

    TicketType * TTptr;
    Default * Dptr;
    Student * Sptr;
    Veteran * Vptr;
    Child * Cptr;
    Other * Optr;
};

BOOST_FIXTURE_TEST_SUITE(TicketTypeTreeTests, TicketTypeTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTests){
        TTptr = new Default();
        BOOST_TEST_REQUIRE(TTptr != nullptr);
                delete TTptr;

        TTptr = new Student();
        BOOST_TEST_REQUIRE(TTptr != nullptr);
                delete TTptr;

        TTptr = new Veteran();
        BOOST_TEST_REQUIRE(TTptr != nullptr);
                delete TTptr;

        TTptr = new Child();
        BOOST_TEST_REQUIRE(TTptr != nullptr);
              delete TTptr;

        TTptr = new Other();
        BOOST_TEST_REQUIRE(TTptr != nullptr);
                delete TTptr;
    }


    BOOST_AUTO_TEST_CASE(GetterTests){

        TTptr = new Default();
        BOOST_TEST(TTptr->getDiscount()==0);
        BOOST_TEST(TTptr->getType()=="Default");
        BOOST_TEST(TTptr->getTypeInfo()=="Ticket type: Default - 0% discount");
        BOOST_TEST(TTptr->applyDiscount(100) == 100.0);
        delete TTptr;

        TTptr = new Student();
        BOOST_TEST(TTptr->getDiscount()==21);
        BOOST_TEST(TTptr->getType()=="Student");
        BOOST_TEST(TTptr->getTypeInfo()=="Ticket type: Student - 21% discount");
        BOOST_TEST((TTptr->applyDiscount(100) >= 78.9 && TTptr->applyDiscount(100) <= 79.1));       //boost::unit_test::tolerance(0.1) throws
        delete TTptr;

        TTptr = new Veteran();
        BOOST_TEST(TTptr->getDiscount()==37);
        BOOST_TEST(TTptr->getType()=="Veteran");
        BOOST_TEST(TTptr->getTypeInfo()=="Ticket type: Veteran - 37% discount");
        BOOST_TEST((TTptr->applyDiscount(100) >= 62.9 && TTptr->applyDiscount(100) <= 63.1));
        delete TTptr;

        TTptr = new Child();
        BOOST_TEST(TTptr->getDiscount()==60);
        BOOST_TEST(TTptr->getType()=="Child");
        BOOST_TEST(TTptr->getTypeInfo()=="Ticket type: Child - 60% discount");
        BOOST_TEST((TTptr->applyDiscount(100) >= 39.9 && TTptr->applyDiscount(100) <= 40.1));
        delete TTptr;

        TTptr = new Other();
        BOOST_TEST(TTptr->getDiscount()==10);
        BOOST_TEST(TTptr->getType()=="Other");
        BOOST_TEST(TTptr->getTypeInfo()=="Ticket type: Other - 10% discount");
        BOOST_TEST((TTptr->applyDiscount(100) >= 89.9 && TTptr->applyDiscount(100) <= 90.1));
        delete TTptr;

    }

BOOST_AUTO_TEST_SUITE_END()