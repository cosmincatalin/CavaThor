#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <signal.h>
#include <librdkafka/rdkafka.h>
#include "car.pb.h"

int main() {
    example::Car car_in;
    car_in.set_serial_number(24334);
    car_in.set_top_speed(23.5);
    car_in.set_number_of_doors(4);
    car_in.set_included_km(342343);
    car_in.set_gearbox_positions(6);
    car_in.set_rentals(343);
    car_in.set_available(true);
    car_in.set_brand("Volvo");
    char buff[1024];
    char* data = buff;
    car_in.SerializeToArray(data, car_in.ByteSize());

    rd_kafka_conf_t* conf = rd_kafka_conf_new();
    rd_kafka_conf_set(conf, "bootstrap.servers", "kafka:9092", nullptr, 0);
    rd_kafka_t* producer = rd_kafka_new(RD_KAFKA_PRODUCER, conf, nullptr, 0);
    conf = nullptr;
    rd_kafka_producev(producer,
                                RD_KAFKA_V_TOPIC("users-pb"),
                                RD_KAFKA_V_MSGFLAGS(RD_KAFKA_MSG_F_COPY),
                                RD_KAFKA_V_VALUE(data, car_in.ByteSize()),
                                RD_KAFKA_V_OPAQUE(NULL),
                                RD_KAFKA_V_END);
    rd_kafka_poll(producer, 0);
    rd_kafka_flush(producer, 1000);
    rd_kafka_destroy(producer);

    dbg(data);

    dbg("Done Kafka P");
    return 0;
}
