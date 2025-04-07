set(APP_NAME source)

cmake_minimum_required(VERSION 3.5)

message("PLUGINS PATH " $ENV{QT_PLUGIN_PATH})

set (CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(graphics)
add_subdirectory(utils)

find_package(Qt6 COMPONENTS
            Widgets 
            Core 
            Gui
            OpenGL
            Network 
            OpenGLWidgets 
            Svg 
            REQUIRED)

set (HEADERS 
    framework/cubewidget.hpp)

set (SOURCES 
    framework/cubewidget.cpp
    main.cpp)

add_executable(${APP_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${APP_NAME} PRIVATE ./ ./framework) #add path

target_link_libraries(${APP_NAME} PRIVATE Qt6::Core)
target_link_libraries(${APP_NAME} PRIVATE Qt6::Gui)
target_link_libraries(${APP_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${APP_NAME} PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(${APP_NAME} PRIVATE Qt6::OpenGL)
target_link_libraries(${APP_NAME} PRIVATE Qt6::Svg)

target_link_libraries(${APP_NAME} PRIVATE graphics)
target_link_libraries(${APP_NAME} PRIVATE utils)



add_custom_command(TARGET ${APP_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   $ENV{QT_PLUGIN_PATH}/platforms
                   $<TARGET_FILE_DIR:${APP_NAME}>/platforms)

add_custom_command(TARGET ${APP_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:Qt6::Core> $<TARGET_FILE_DIR:${APP_NAME}>)

add_custom_command(TARGET ${APP_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:Qt6::Gui> $<TARGET_FILE_DIR:${APP_NAME}>)

add_custom_command(TARGET ${APP_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:Qt6::Widgets> $<TARGET_FILE_DIR:${APP_NAME}>)

add_custom_command(TARGET ${APP_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:Qt6::OpenGLWidgets> $<TARGET_FILE_DIR:${APP_NAME}>)

add_custom_command(TARGET ${APP_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:Qt6::OpenGL> $<TARGET_FILE_DIR:${APP_NAME}>)

add_custom_command(TARGET ${APP_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:Qt6::Svg> $<TARGET_FILE_DIR:${APP_NAME}>)