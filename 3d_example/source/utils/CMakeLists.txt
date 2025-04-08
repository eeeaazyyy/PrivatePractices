set(APP_NAME utils)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set (CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

set(HEADERS
    test/alert.hpp
    test/customclass.hpp
    test/alertTest/alertscontroller.hpp
    test/alertTest/alertmodel.hpp
    include/alertgenerator.hpp
    include/delaywidgetcontroller.hpp
    include/timeprofiler.hpp
    )

set(SOURCES
    test/src/alert.cpp
    test/alertTest/alertscontroller.cpp
    test/alertTest/alertmodel.cpp
    test/alertTest/testfile.cpp
    src/alertgenerator.cpp
    src/delaywidgetcontroller.cpp
    src/timeprofiler.cpp
    )

add_library(${APP_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${APP_NAME} PRIVATE . ../ ../graphics/editor ./include ./src ./scene ./domain ./test ./test/alertTest)

target_link_libraries(${APP_NAME} PRIVATE Qt6::Core)
target_link_libraries(${APP_NAME} PRIVATE Qt6::Gui)
target_link_libraries(${APP_NAME} PRIVATE Qt6::Widgets)

install(TARGETS ${APP_NAME}
        RUNTIME DESTINATION ${INSTALL_DIRECTORY} LIBRARY DESTINATION ${INSTALL_DIRECTORY})
