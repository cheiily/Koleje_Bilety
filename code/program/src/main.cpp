#include<iostream>
#include"UnitHierarchy/ElectricMultipleUnit.h"
#include"TicketTypeHierarchy/Student.h"
#include "Managers/LineManager.h"
#include "Managers/TicketManager.h"
#include "Managers/UnitManager.h"
#include "TicketTypeHierarchy/Child.h"
#include "TicketTypeHierarchy/Default.h"
#include "TicketTypeHierarchy/Veteran.h"

using namespace std;
int main()
{
    LineManager lm;

    UnitManager um1;
    UnitManager um2;

    TicketManager tm(1);


    //scenariusz przykladowy

    um1.registerElectricExpress("EP35-001","Electric Bolt Turbo", "Germany", "Tesla", 2020, 400, 314159265359,200, "PKP", 1,5,1000.213);
    um1.registerDieselExpress("SU27ICC-578","Yugo Express", "Yugoslavia", "YNLM", 1950, 120, 999999999999, 400, "ICC", 1,40,12343.1233 );
    um1.registerEMU("EW91-1466ra","EMU","USA","Ostrich&Emu factory",2000,430,120010201,500,"SKM",4);

    um2.registerTram("104Nt","Konstal1", "Poland","PZT", 1840,50,50505050,100,"Lodz",true);
    um2.registerTram("105Nt","Konstal2", "Poland","PZT", 1841,70,45645645,100,"Lodz",true);
    um2.registerTram("824G8ZR","Mod14", "Poland","PZT", 1990,100,540000,50,"Lodz",false);
    um2.registerRailBus("SA105-001", "Regio Tramp", "Poland", "ZNTK Poznan", 2002, 100, 250000, 205, "Leszno");
    um2.registerRailBus("DBVT98-9796", "Baureihe", "Germany", "MAN Nurnberg AG", 1961, 90, 150000, 58, "Linz am Rhein");

    Node WAR = {"Warsaw", 148.89, pt::ptime(boost::gregorian::from_undelimited_string("20220613"))+pt::hours(13)+pt::minutes(59), pt::ptime(boost::gregorian::from_undelimited_string("20220613"))+pt::hours(13)+pt::minutes(2)};
    Node LOD = {"Boat city", 51.3, pt::ptime(boost::gregorian::from_undelimited_string("20220613"))+pt::hours(12) + pt::minutes(38), pt::ptime(boost::gregorian::from_undelimited_string("20220613"))+pt::hours(12)+pt::minutes(41)};
    Node TOM = {"Tomaszow Maz", 0, pt::ptime(boost::gregorian::from_undelimited_string("20220613"))+pt::hours(12), pt::ptime(boost::gregorian::from_undelimited_string("20220613"))+pt::hours(12)+pt::minutes(1)};
    Node WRO = {"Breslau", 272.54, pt::ptime(boost::gregorian::from_undelimited_string("20220613"))+pt::hours(16)+pt::minutes(31), pt::ptime(boost::gregorian::from_undelimited_string("20220613"))+pt::hours(14)+pt::minutes(24)};

    NodePtr node1 = std::make_shared<Node>(WAR);
    NodePtr node2 = std::make_shared<Node>(LOD);
    NodePtr node3 = std::make_shared<Node>(TOM);
    NodePtr node4 = std::make_shared<Node>(WRO);
    std::vector<NodePtr> route1;
    std::vector<NodePtr> route2;

    route1 ={node3,node2,node1};
    route2={node3, node1, node4};

    lm.addNewLine("Tom-Lod-War",route1, um1.getUnit("1"));
    lm.addNewLine("Tom-War-Wro", route2, um1.getUnit("2"));

    Transit t1= Transit("Tom-War",route1,um1.getUnit("1"));
    TransitPtr transit1 = make_shared<Transit>(t1);


    Transit t2 = Transit("Tom-Wro",route2,um1.getUnit("2"));
    TransitPtr transit2 = make_shared<Transit>(t2);

    TicketTypePtr TicketType1;
    TicketType1 = make_shared<Student>();

    TicketTypePtr TicketType2;
    TicketType2 = make_shared<Default>();

    TicketTypePtr TicketType3;
    TicketType3 = make_shared<Child>();

    TicketTypePtr TicketType4;
    TicketType4 = make_shared<Veteran>();

    tm.issueTicket(TicketType1,transit1);
    tm.issueTicket(TicketType2, transit1);
    tm.issueTicket(TicketType2,transit2);
    tm.issueTicket(TicketType3, transit2);
    tm.issueTicket(TicketType4, transit2);

    TicketPtr validated1 = tm.findAllTickets().at(1);
    tm.validateTicket(validated1);
    TicketPtr returned1 = tm.findAllTickets().at(3);
    tm.validateTicket(returned1);

    cout<<"Jednostki zarzadzane przez menagera um1: ";
    for(int i=0; i<um1.findAllUnits().size(); i++)
    {
        cout<<endl<<um1.findAllUnits()[i]->getInfo();
    }

    cout<<endl<<endl<<"Jednostki zarzadzane przez menagera um2: ";
    for(int i=0; i<um2.findAllUnits().size();i++)
    {
        cout<<endl<<um2.findAllUnits()[i]->getUnitInfo();
    }

    cout<<endl<<endl<<"Linie zarzadzane przez menagera lm: ";
    for(int i=0; i<lm.findAllLines().size(); i++)
    {
        cout<<endl<<lm.findAllLines()[i]->getInfo();
    }

    cout<<endl<<endl<<"Bilety zarzadzane przez menagera tm: ";
    for(int i=0; i<tm.findAllTickets().size(); i++)
    {
        cout<<endl<<tm.findAllTickets()[i]->getInfo();
    }


    return EXIT_SUCCESS;
}
