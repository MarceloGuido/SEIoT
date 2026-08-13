#include "wifi.h"
#include "mdns.h"
#include "gpio.h"
#include "dht.h"
#include "webserver.h"

void setup()
{
    Serial.begin(115200);
    Serial.println();

    conectarWiFi();

    iniciarMDNS();

    iniciarGPIO();

    iniciarDHT();

    iniciarServidor();
}

void loop()
{
    atualizarDHT();

    atualizarMDNS();

    processarServidor();
}