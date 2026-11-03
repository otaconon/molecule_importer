cmake_minimum_required(VERSION 3.30)
project(molecule_importer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GODOTCPP_API_VERSION "4.7" CACHE STRING "Godot API Version")
add_subdirectory(godot-cpp)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/bin"
)

find_library(CAIRO_LIBRARY NAMES cairo REQUIRED)
find_path(CAIRO_INCLUDE_DIR NAMES cairo.h PATH_SUFFIXES cairo REQUIRED)

if(NOT TARGET Cairo::Cairo)
    add_library(Cairo::Cairo INTERFACE IMPORTED)
    set_target_properties(Cairo::Cairo PROPERTIES
            INTERFACE_LINK_LIBRARIES      "${CAIRO_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${CAIRO_INCLUDE_DIR}"
    )
endif()

# Pass -DCMAKE_PREFIX_PATH="C:/path/to/rdkit" when configuring
find_package(RDKit CONFIG REQUIRED)
get_filename_component(RDKIT_BIN "${RDKit_DIR}/../../../bin" ABSOLUTE)
message(STATUS "RDKit_DIR = ${RDKit_DIR}")
message(STATUS "RDKIT_BIN = ${RDKIT_BIN}")

target_compile_definitions(${PROJECT_NAME} PRIVATE RDKIT_DYN_LINK)
target_link_libraries(${PROJECT_NAME} PRIVATE
        godot::cpp
        RDKit::GraphMol
        RDKit::FileParsers
        RDKit::RDGeometryLib
        RDKit::RDGeneral
        RDKit::SmilesParse
        RDKit::MolDraw2D
)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            "-DTARGET_FILE=$<TARGET_FILE:${PROJECT_NAME}>"
            "-DOUTPUT_DIR=$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            "-DSEARCH_DIR=${RDKIT_BIN}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyDlls.cmake"
            COMMENT "Scanning PE imports and copying required DLLs..."
    )
endif()
