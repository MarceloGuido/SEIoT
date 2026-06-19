#include "wifi.h"

void setup()
{
    Serial.begin(115200);
    Serial.println();

    conectarWiFi();

    delay(1000);
}

void loop()
{
}
