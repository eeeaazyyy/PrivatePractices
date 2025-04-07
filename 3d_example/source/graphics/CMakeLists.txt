set(APP_NAME graphics)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set (CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Widgets Core Gui Svg REQUIRED)

set(HEADERS
    mainwindow/mainwindow.hpp
    editor/graphicseditor.hpp
    scene/graphicsview.hpp)

set(SOURCES
    mainwindow/mainwindow.cpp
    editor/graphicseditor.cpp
    scene/graphicsview.cpp)

add_library(${APP_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${APP_NAME} PRIVATE . ../ ./editor ./scene ../utils ../utils/test)

target_link_libraries(${APP_NAME} PRIVATE Qt6::Core)
target_link_libraries(${APP_NAME} PRIVATE Qt6::Gui)
target_link_libraries(${APP_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${APP_NAME} PRIVATE Qt6::Svg)

target_link_libraries(${APP_NAME} PRIVATE utils)

install(TARGETS ${APP_NAME}
        RUNTIME DESTINATION ${INSTALL_DIRECTORY} LIBRARY DESTINATION ${INSTALL_DIRECTORY})
