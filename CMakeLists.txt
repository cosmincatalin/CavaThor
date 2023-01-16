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
find_package(Protobuf CONFIG REQUIRED)
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

add_executable(KafkaProtoProducer src/kafka-proto-producer/producer.cpp src/proto/car.pb.h src/proto/car.pb.cc)
target_include_directories(
    KafkaProtoProducer
    PRIVATE ${DBG_MACRO_INCLUDE_DIRS}
)
target_link_libraries(
    KafkaProtoProducer
    PRIVATE RdKafka::rdkafka RdKafka::rdkafka++
)
target_link_libraries(
    KafkaProtoProducer
    PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
)

add_executable(KafkaProtoConsumer src/kafka-proto-consumer/consumer.cpp src/proto/car.pb.h src/proto/car.pb.cc)
target_include_directories(
    KafkaProtoConsumer
    PRIVATE ${DBG_MACRO_INCLUDE_DIRS}
)
target_link_libraries(
    KafkaProtoConsumer
    PRIVATE RdKafka::rdkafka RdKafka::rdkafka++
)
target_link_libraries(
    KafkaProtoConsumer
    PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
)
