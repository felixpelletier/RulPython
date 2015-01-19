cmake_minimum_required(VERSION 2.8.4)
project(RulFramework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Install Proto
if(NOT PROTO_INSTALLED)
    execute_process(
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/proto/install.sh
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

#Threads
find_package(Threads REQUIRED)

#boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ALL_DYN_LINK ON)

find_package(Boost COMPONENTS filesystem system program_options thread log log_setup REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

# Protobuf
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_executable(RulFramework main.cpp ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(RulFramework rule-ssl rule-streams rule-exception ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES})

set(PROTO_INSTALLED TRUE CACHE INTERNAL
    "Proto has already been installed")