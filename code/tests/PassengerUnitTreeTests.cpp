#include <boost/test/unit_test.hpp>
#include "UnitHierarchy/Railbus.h"
#include "UnitHierarchy/Tram.h"
#include "UnitHierarchy/ElectricMultipleUnit.h"
#include "UnitHierarchy/ElectricExpress.h"
#include "UnitHierarchy/DieselExpress.h"
#include "Exceptions.h"

using namespace std;

struct UnitTestSuiteFixture {
    string testUnitID = "0001";
    string testUnitName = "EU07-364";
    int testManufacturingYear = 1985;
    string testCountryOfOrigin = "Poland";
    int testMaxVelocity = 125;
    string testManufacturer = "Pafawag";
    long testMileage = 2000000;
    int testCapacity = 200;
    string testCarrier = "PKP Cargo";
    int testLocoQuantity = 2;
    int testCarQuantity = 43;
    double testSupplyVoltage = 3000.1;
    double testEngineDisplacement = 14.1;
    string testCity = "Lodz";
    int testEMUQuantity = 3;
    bool testComposite = true;


    PassengerUnit * puptr;
    Railbus * rptr;
    Tram * tptr;
    ElectricMultipleUnit * emuptr;
    ElectricExpress * eeptr;
    DieselExpress * deptr;
    
};

BOOST_FIXTURE_TEST_SUITE(PassengerUnitTreeTests, UnitTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTests) {
        puptr = new Railbus(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCity);
        BOOST_TEST_REQUIRE(puptr != nullptr);
        BOOST_TEST(puptr->isArchive() == false);
        delete puptr;

        puptr = new Tram(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCity, testComposite);
        BOOST_TEST_REQUIRE(puptr != nullptr);
        BOOST_TEST(puptr->isArchive() == false);
        delete puptr;

        puptr = new ElectricMultipleUnit(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testEMUQuantity);
        BOOST_TEST_REQUIRE(puptr != nullptr);
        BOOST_TEST(puptr->isArchive() == false);
        delete puptr;

        puptr = new ElectricExpress(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testLocoQuantity, testCarQuantity, testSupplyVoltage);
        BOOST_TEST_REQUIRE(puptr != nullptr);
        BOOST_TEST(puptr->isArchive() == false);
        delete puptr;

        puptr = new DieselExpress(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testLocoQuantity, testCarQuantity, testEngineDisplacement);
        BOOST_TEST_REQUIRE(puptr != nullptr);
        BOOST_TEST(puptr->isArchive() == false);
        delete puptr;
    }


    BOOST_AUTO_TEST_CASE(GetterSetterTests) {
        rptr = new Railbus(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCity);
        BOOST_TEST(rptr->getUnitID() == testUnitID);
        BOOST_TEST(rptr->getUnitName() == testUnitName);
        BOOST_TEST(rptr->getCountryOfOrigin() == testCountryOfOrigin);
        BOOST_TEST(rptr->getManufacturer() == testManufacturer);
        BOOST_TEST(rptr->getManufacturingYear() == testManufacturingYear);
        BOOST_TEST(rptr->getMaxVelocity() == testMaxVelocity);
        BOOST_TEST(rptr->getMileage() == testMileage);
        BOOST_TEST(rptr->getCapacity() == testCapacity);
        BOOST_TEST(rptr->getCity() == testCity);

        testMileage += 6666;
        testCapacity += 6;
        testUnitName += "\b6";
        testCity = "Boat City";

        rptr->setMileage(testMileage);
        rptr->setCapacity(testCapacity);
        rptr->setUnitName(testUnitName);
        rptr->setCity(testCity);
        rptr->setArchive(true);

        BOOST_TEST(rptr->getUnitName() == testUnitName);
        BOOST_TEST(rptr->getMileage() == testMileage);
        BOOST_TEST(rptr->getCapacity() == testCapacity);
        BOOST_TEST(rptr->getCity() == testCity);
        BOOST_TEST(rptr->isArchive() == true);

        delete rptr;
        tptr = new Tram(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCity, testComposite);

        BOOST_TEST(tptr->isComposite() == testComposite);
        testComposite = !testComposite;
        tptr->setComposite(testComposite);
        BOOST_TEST(tptr->isComposite() == testComposite);
        delete tptr;

        emuptr = new ElectricMultipleUnit(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testEMUQuantity);
        BOOST_TEST(emuptr->getCarrier() == testCarrier);
        BOOST_TEST(emuptr->getUnitQuantity() == testEMUQuantity);

        testCarrier = "PKP Intercity";
        testEMUQuantity -= 1;
        emuptr->setCarrier(testCarrier);
        emuptr->setUnitQuantity(testEMUQuantity);

        BOOST_TEST(emuptr->getCarrier() == testCarrier);
        BOOST_TEST(emuptr->getUnitQuantity() == testEMUQuantity);
        delete emuptr;

        eeptr = new ElectricExpress(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testLocoQuantity, testCarQuantity, testSupplyVoltage);
        BOOST_TEST(eeptr->getLocomotiveQuantity() == testLocoQuantity);
        BOOST_TEST(eeptr->getCarQuantity() == testCarQuantity);
        BOOST_TEST(eeptr->getSupplyVoltage() == testSupplyVoltage);

        testLocoQuantity += 1;
        testCarQuantity -= 14;
        testSupplyVoltage /= 2;
        eeptr->setLocomotiveQuantity(testLocoQuantity);
        eeptr->setCarQuantity(testCarQuantity);
        eeptr->setSupplyVoltage(testSupplyVoltage);

        BOOST_TEST(eeptr->getLocomotiveQuantity() == testLocoQuantity);
        BOOST_TEST(eeptr->getCarQuantity() == testCarQuantity);
        BOOST_TEST(eeptr->getSupplyVoltage() == testSupplyVoltage);
        delete eeptr;

        deptr = new DieselExpress(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testLocoQuantity, testCarQuantity, testEngineDisplacement);
        BOOST_TEST(deptr->getEngineDisplacement() == testEngineDisplacement);

        testEngineDisplacement += 215;
        deptr->setEngineDisplacement(testEngineDisplacement);

        BOOST_TEST(deptr->getEngineDisplacement() == testEngineDisplacement);
        delete deptr;

    }


    BOOST_AUTO_TEST_CASE(PolimorphicGetterTests) {
        puptr = new Tram(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCity, testComposite);
        BOOST_TEST(puptr->getInfo().find("Composite") != string::npos);
        delete puptr;

        puptr = new DieselExpress(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testLocoQuantity, testCarQuantity, testEngineDisplacement);
        string tInfo = puptr->getInfo();
        BOOST_TEST(tInfo.find(testCarrier) != string::npos);
        BOOST_TEST(tInfo.find(std::to_string(testEngineDisplacement)) != string::npos);
        BOOST_TEST(tInfo.find(std::to_string(testLocoQuantity)) != string::npos);
        delete puptr;
    }


    BOOST_AUTO_TEST_CASE(NegativeConstructorAndSetterTests) {
        BOOST_CHECK_THROW(puptr = new Railbus("", testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCity), EmptyStringException);
        
        try { puptr = new Railbus("", testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCity);
        } catch (const std::logic_error & ex) { BOOST_TEST(string(ex.what()).find("unitID") != string::npos); }
        try { puptr = new Railbus(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, 0, testCapacity, testCity);
        } catch (const std::logic_error & ex) { BOOST_TEST(string(ex.what()).find("mileage") != string::npos); }

        puptr = new Railbus(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCity);
        try { puptr->setMileage(-1);
        } catch (const std::logic_error & ex) { BOOST_TEST(string(ex.what()).find("mileage") != string::npos); }
        delete puptr;
        
        
        try { emuptr = new ElectricMultipleUnit(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, 0);
        } catch (const std::logic_error & ex) { BOOST_TEST(string(ex.what()).find("unitQuantity") != string::npos); }
        
        emuptr = new ElectricMultipleUnit(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testEMUQuantity);
        try { emuptr->setUnitQuantity(0); } catch (const std::logic_error & ex) 
        { BOOST_TEST(string(ex.what()).find("unitQuantity") != string::npos); }
        delete emuptr;


        eeptr = new ElectricExpress(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testLocoQuantity, testCarQuantity, testSupplyVoltage);
        try { eeptr->setSupplyVoltage(0); } catch (const std::logic_error & ex)
        { BOOST_TEST(string(ex.what()).find("supplyVoltage") != string::npos); }
        try { eeptr->setLocomotiveQuantity(0); } catch (const std::logic_error & ex)
        { BOOST_TEST(string(ex.what()).find("locomotiveQuantity") != string::npos); }
        try { eeptr->setCarQuantity(0); } catch (const std::logic_error & ex)
        { BOOST_TEST(string(ex.what()).find("carQuantity") != string::npos); }
        delete eeptr;

        try { eeptr = new ElectricExpress(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testLocoQuantity, testCarQuantity, 0);
        } catch (const std::logic_error & ex) { BOOST_TEST(string(ex.what()).find("supplyVoltage") != string::npos); }
        try { eeptr = new ElectricExpress(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, 0, testCarQuantity, testSupplyVoltage);
        } catch (const std::logic_error & ex) { BOOST_TEST(string(ex.what()).find("locomotiveQuantity") != string::npos); }
        try { eeptr = new ElectricExpress(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testLocoQuantity, 0, testSupplyVoltage);
        } catch (const std::logic_error & ex) { BOOST_TEST(string(ex.what()).find("carQuantity") != string::npos); }


        deptr = new DieselExpress(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testLocoQuantity, testCarQuantity, testEngineDisplacement);
        try { deptr->setEngineDisplacement(0); } catch (const std::logic_error & ex)
        { BOOST_TEST(string(ex.what()).find("engineDisplacement") != string::npos); }
        delete deptr;

        try { deptr = new DieselExpress(testUnitID, testUnitName, testCountryOfOrigin, testManufacturer, testManufacturingYear, testMaxVelocity, testMileage, testCapacity, testCarrier, testLocoQuantity, testCarQuantity, 0);
        } catch (const std::logic_error & ex) { BOOST_TEST(string(ex.what()).find("engineDisplacement") != string::npos); }

    }



BOOST_AUTO_TEST_SUITE_END()