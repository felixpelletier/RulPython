cmake_minimum_required(VERSION 2.8.4)
project(RulFramework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fPIC -std=c++11")

add_subdirectory(RuleSSL)

#Install Proto
if(NOT PROTO_INSTALLED)
    execute_process(
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/proto/install.sh
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

#Threads
find_package(Threads REQUIRED)

# Python
set(Python_ADDITIONAL_VERSIONS 3.4)
FIND_PACKAGE(PythonLibs 3 REQUIRED)
FIND_PATH(PYTHON_INCLUDE_PATH Python.h
  /usr/include
  /usr/local/include)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})
link_directories(${PYTHON_LIBRARIES})
SET(PYTHON_BINARIES /usr/bin/python3)

#boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ALL_DYN_LINK ON)

find_package(Boost COMPONENTS filesystem system program_options thread log log_setup python3 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

# Protobuf
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/RuleSSL/RuleMain/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/RuleSSL/Exception/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/RuleSSL/Streams/include")

add_executable(RulFramework main.cpp ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(RulFramework rule-ssl rule-streams rule-exception ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${PROTOBUF_LIBRARIES})

add_subdirectory(Python)

add_custom_target(copy_test_assets)
add_dependencies(RulFramework copy_test_assets rule_python)
add_custom_command(TARGET copy_test_assets POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
       copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/scripts ${CMAKE_CURRENT_BINARY_DIR}/scripts)

set(PROTO_INSTALLED TRUE CACHE INTERNAL
    "Proto has already been installed")
