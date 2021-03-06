#include "mqtt_client.h"

#define CLIENT_ID "Client_ID"
#define BROKER_ADDRESS "localhost"
#define MQTT_PORT 1883
#define MQTT_TOPPIC "EXAMPLE_TOPIC"

int main(int argc, char *argv[])
{
    class mqtt_client *iot_client;
    int rc;

    char client_id[] = CLIENT_ID;
    char host[] = BROKER_ADDRESS;
    int port = MQTT_PORT;

    if (argc > 1) {
        strcpy(host, argv[1]);
    }

    iot_client = new mqtt_client(client_id, host, port);

    while(1) {
        rc = iot_client->loop();
        if (rc) {
            iot_client->reconnect();
        }
        else {
            iot_client->subscribe(NULL, MQTT_TOPPIC);
        }
    }

    return 0;
}
