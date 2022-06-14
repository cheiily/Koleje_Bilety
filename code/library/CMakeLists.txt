cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
        include/typedefs.h
        include/Exceptions.h
        include/UnitHierarchy/PassengerUnit.h src/UnitHierarchy/PassengerUnit.cpp
        include/UnitHierarchy/IntercityUnit.h src/UnitHierarchy/IntercityUnit.cpp include/UnitHierarchy/UrbanUnit.h src/UnitHierarchy/UrbanUnit.cpp include/UnitHierarchy/Express.h src/UnitHierarchy/Express.cpp include/UnitHierarchy/ElectricMultipleUnit.h src/UnitHierarchy/ElectricMultipleUnit.cpp include/UnitHierarchy/DieselExpress.h src/UnitHierarchy/DieselExpress.cpp include/UnitHierarchy/ElectricExpress.h src/UnitHierarchy/ElectricExpress.cpp src/UnitHierarchy/Railbus.cpp include/UnitHierarchy/Railbus.h src/UnitHierarchy/Tram.cpp include/UnitHierarchy/Tram.h
        src/TicketTypeHierarchy/TicketType.cpp include/TicketTypeHierarchy/Default.h src/TicketTypeHierarchy/Default.cpp include/TicketTypeHierarchy/Student.h src/TicketTypeHierarchy/Student.cpp include/TicketTypeHierarchy/Veteran.h src/TicketTypeHierarchy/Veteran.cpp include/TicketTypeHierarchy/Child.h src/TicketTypeHierarchy/Child.cpp include/TicketTypeHierarchy/Other.h src/TicketTypeHierarchy/Other.cpp
        include/Model/ValidationState.h
        src/Model/Ticket.cpp include/Model/Ticket.h
        include/Model/Node.h src/Model/Line.cpp include/Model/Line.h src/Model/Transit.cpp include/Model/Transit.h
        include/Repositories/Repository.h include/Repositories/UnitRepository.h src/Repositories/UnitReposotory.cpp include/Repositories/TicketRepository.h src/Repositories/TicketRepository.cpp include/Repositories/LineReposotory.h src/Repositories/LineReposotory.cpp
        include/Managers/UnitManager.h include/Managers/TicketManager.h include/Managers/LineManager.h src/Managers/LineManager.cpp src/Managers/TicketManager.cpp src/Managers/UnitManager.cpp)

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
