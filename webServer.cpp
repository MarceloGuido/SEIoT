#include <ESP8266WiFi.h>

#include "webserver.h"
#include "gpio.h"
#include "html.h"

WiFiServer server(80);

String header;

void iniciarServidor()
{
    server.begin();

    Serial.println("Servidor iniciado");
}
