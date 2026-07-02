#include "wifi.h"
#include "mdns.h"
#include "gpio.h"
#include "webserver.h"

void setup()
{
    Serial.begin(115200);

    conectarWiFi();

    iniciarMDNS();

    iniciarGPIO();

    iniciarServidor();
}

void loop()
{
    atualizarMDNS();
    processarServidor();
}
