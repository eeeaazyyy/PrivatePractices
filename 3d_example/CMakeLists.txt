cmake_minimum_required(VERSION 3.5)

project (3D_Example)

set(CMAKE_CXX_STANDARD 17)

set(INSTALL_DIRECTORY 
        ${PROJECT_BINARY_DIR}/deploy
        CACHE PATH
        "Install directory")

file(MAKE_DIRECTORY ${INSTALL_DIRECTORY})
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all")

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all")

add_subdirectory(source)