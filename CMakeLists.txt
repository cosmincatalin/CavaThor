cmake_minimum_required(VERSION 3.23.0)

project(CavaThor
        VERSION 1.0.0
        DESCRIPTION "A customizable Kafka sink for offloading data to other storage solutions. Break free from the rigid Confluent connectors and synchronize your data the way you want it. Built-in implementations include SQLite and Redis, but you can easily add your own integrations."
        HOMEPAGE_URL ""
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(src)

find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")
find_package(hiredis CONFIG REQUIRED)
#find_package(Threads REQUIRED)

#add_library(CavaThor SHARED src/Replicator.cpp src/Replicator.hpp src/Destinations/RedisDestination.cpp src/Destinations/RedisDestination.hpp)
#target_include_directories(CavaThor PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
#target_link_libraries(CavaThor PUBLIC Threads::Threads)
#target_link_libraries(CavaThor PRIVATE hiredis::hiredis)
#install(TARGETS CavaThor)

add_executable(Synchronize runners/Synchronize.cpp)
target_include_directories(Synchronize PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
target_link_libraries(Synchronize PRIVATE hiredis::hiredis)
#target_link_libraries(Synchronize CavaThor)
