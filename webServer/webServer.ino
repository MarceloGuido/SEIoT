#include "wifi.h"
#include "gpio.h"
#include "webserver.h"

void setup()
{
    Serial.begin(115200);

    conectarWiFi();

    iniciarGPIO();

    iniciarServidor();
}

void loop()
{
    processarServidor();
}

