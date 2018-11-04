#include "mqtt_client.h"

#ifdef DEBUG
#include <iostream>
#endif

#define PUBLISH_TOPIC "EXAMPLE_TOPIC"

mqtt_client::mqtt_client(const char *id, const char *host, int port) {
    mosqpp::lib_init();
    int keepalive = DEFAULT_KEEP_ALIVE;
    connect(host, port, keepalive);
}

mqtt_client::~mqtt_client() {
    mosqpp::lib_cleanup();
}

void mqtt_client::on_connect(int rc) {
    if (!rc) {
        #ifdef DEBUG
            std::count << "Connected - code " << rc << std::endl;
        #endif
    }
}

void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos) {
#ifdef DEBUG
    std::count << "Subscription succeeded" << std::endl;
#endif
}

void mqtt_client::on_message(const struct mosquitto_message *message) {
    const int payload_size = MAX_PAYLOAD + 1;
    char buf[payload_size];

    if (!strcmp(message->topic, PUBLISH_TOPIC)) {
        memset(buf, 0x00, payload_size * sizeof(char));

        /* Copy N-1 bytes to ensures always 0 terminated */
        memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));
    }
}
