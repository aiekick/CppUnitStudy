cmake_minimum_required(VERSION 3.20)

set(PROJECT CppUnitStudy)

enable_language(CXX)
project(${PROJECT} CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CmakeTargets")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/cppunit.cmake)

file(GLOB_RECURSE SRC_SOURCES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp
	${CMAKE_SOURCE_DIR}/src/*.cpp
)
source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX src FILES ${SRC_SOURCES})

add_executable(${PROJECT} ${SRC_SOURCES})

target_include_directories(${PROJECT} PRIVATE ${CPPUNIT_INCLUDE_DIR})

target_link_libraries(${PROJECT} PRIVATE ${CPPUNIT_LIBRARY})
