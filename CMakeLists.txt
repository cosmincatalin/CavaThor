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
find_package(RdKafka CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
#find_package(Threads REQUIRED)

#add_library(CavaThor SHARED src/Replicator.cpp src/Replicator.hpp src/Destinations/RedisDestination.cpp src/Destinations/RedisDestination.hpp)
#target_include_directories(CavaThor PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
#target_link_libraries(CavaThor PUBLIC Threads::Threads)
#target_link_libraries(CavaThor PRIVATE hiredis::hiredis)
#install(TARGETS CavaThor)

add_executable(RedisProducer runners/redis-producer.cpp)
target_include_directories(RedisProducer PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
target_link_libraries(RedisProducer PRIVATE hiredis::hiredis)

add_executable(KafkaConsumer runners/kafka-consumer.cpp runners/user.pb.h runners/user.pb.cc)
target_include_directories(KafkaConsumer PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
target_link_libraries(KafkaConsumer PRIVATE RdKafka::rdkafka RdKafka::rdkafka++)
target_link_libraries(KafkaConsumer PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

add_executable(KafkaProducer runners/kafka-producer.cpp runners/user.pb.h runners/user.pb.cc)
target_include_directories(KafkaProducer PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
target_link_libraries(KafkaProducer PRIVATE RdKafka::rdkafka RdKafka::rdkafka++)
target_link_libraries(KafkaProducer PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

add_executable(ProtobufProducer runners/protobuf-producer.cpp runners/user.pb.h runners/user.pb.cc)
target_include_directories(ProtobufProducer PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
target_link_libraries(ProtobufProducer PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

#target_link_libraries(Synchronize CavaThor)
