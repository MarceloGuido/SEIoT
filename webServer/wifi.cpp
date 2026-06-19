#include <ESP8266WiFi.h>
#include "config.h"
#include "wifi.h"

void conectarWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WLAN_SSID, WLAN_PASS);

    Serial.print("Conectando");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println();
    Serial.print("Conectado | Endereço IP: ");
    Serial.println(WiFi.localIP());
}
