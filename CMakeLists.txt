cmake_minimum_required(VERSION 3.23.0)

project(
    CavaThor
    VERSION 1.0.0
    DESCRIPTION
        "A customizable Kafka sink for offloading data to other storage solutions. Break free from the rigid Confluent connectors and synchronize your data the way you want it. Built-in implementations include SQLite and Redis, but you can easily add your own integrations."
    HOMEPAGE_URL " "
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(src)

find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")
find_package(hiredis CONFIG REQUIRED)
find_package(RdKafka CONFIG REQUIRED)
find_package(Threads REQUIRED)

add_executable(KafkaSimpleProducer src/kafka-simple-producer/producer.cpp)
target_include_directories(
    KafkaSimpleProducer
    PRIVATE ${DBG_MACRO_INCLUDE_DIRS}
)
target_link_libraries(
    KafkaSimpleProducer
    PRIVATE RdKafka::rdkafka RdKafka::rdkafka++
)

add_executable(KafkaSimpleConsumer src/kafka-simple-consumer/consumer.cpp)
target_include_directories(
    KafkaSimpleConsumer
    PRIVATE ${DBG_MACRO_INCLUDE_DIRS}
)
target_link_libraries(
    KafkaSimpleConsumer
    PRIVATE RdKafka::rdkafka RdKafka::rdkafka++
)

#add_executable(
#    KafkaConsumer
#    runners/kafka-consumer.cpp
#    runners/Raw2Redis.hpp
#    runners/Raw2Redis.cpp
#    runners/Replicator.cpp
#    runners/Replicator.hpp
#)
#target_include_directories(KafkaConsumer PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
#target_link_libraries(KafkaConsumer PRIVATE hiredis::hiredis)
#target_link_libraries(KafkaConsumer PRIVATE RdKafka::rdkafka RdKafka::rdkafka++)
