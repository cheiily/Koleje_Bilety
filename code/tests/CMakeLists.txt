enable_testing()

find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        master.cpp
        ../library/include/typedefs.h
        ../library/include/Exceptions.h
        ../library/include/UnitHierarchy/PassengerUnit.h ../library/src/UnitHierarchy/PassengerUnit.cpp ../library/include/UnitHierarchy/IntercityUnit.h ../library/src/UnitHierarchy/IntercityUnit.cpp ../library/include/UnitHierarchy/UrbanUnit.h ../library/src/UnitHierarchy/UrbanUnit.cpp ../library/include/UnitHierarchy/Express.h ../library/src/UnitHierarchy/Express.cpp ../library/include/UnitHierarchy/ElectricMultipleUnit.h ../library/src/UnitHierarchy/ElectricMultipleUnit.cpp ../library/include/UnitHierarchy/DieselExpress.h ../library/src/UnitHierarchy/DieselExpress.cpp ../library/include/UnitHierarchy/ElectricExpress.h ../library/src/UnitHierarchy/ElectricExpress.cpp ../library/src/UnitHierarchy/Railbus.cpp ../library/include/UnitHierarchy/Railbus.h ../library/src/UnitHierarchy/Tram.cpp ../library/include/UnitHierarchy/Tram.h
        PassengerUnitTreeTests.cpp
        ../library/include/TicketTypeHierarchy/TicketType.h ../library/src/TicketTypeHierarchy/TicketType.cpp ../library/include/TicketTypeHierarchy/Child.h ../library/src/TicketTypeHierarchy/Child.cpp ../library/include/TicketTypeHierarchy/Default.h ../library/src/TicketTypeHierarchy/Default.cpp ../library/include/TicketTypeHierarchy/Other.h ../library/src/TicketTypeHierarchy/Other.cpp ../library/include/TicketTypeHierarchy/Student.h ../library/src/TicketTypeHierarchy/Student.cpp ../library/include/TicketTypeHierarchy/Veteran.h ../library/src/TicketTypeHierarchy/Veteran.cpp
        TicketTypeTreeTests.cpp
        ../library/include/Model/Ticket.h ../library/src/Model/Ticket.cpp
        ../library/include/Model/ValidationState.h
        TicketTests.cpp
        ../library/include/Model/Node.h ../library/src/Model/Line.cpp ../library/include/Model/Line.h ../library/src/Model/Transit.cpp ../library/include/Model/Transit.h
        LineTests.cpp TransitTests.cpp RepositoriesTests.cpp ManagersTests.cpp)
add_executable (LibraryTest ${SOURCE_TEST_FILES})

target_link_libraries (LibraryTest
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )


add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
