#include "wifi.h"
#include "mdns.h"
#include "dht.h"
#include "webserver.h"
#include "display.h"

void setup()
{
    Serial.begin(115200);
    Serial.println();

    conectarWiFi();
    iniciarMDNS();

    // Inicializa os módulos e suas respectivas Tasks no FreeRTOS
    iniciarDHT();
    iniciarDisplay();
    iniciarServidor();
}

void loop()
{
    // O RTOS (Scheduler) assume a CPU. 
    // O loop apenas aguarda para evitar acionamento do Watchdog Timer.
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
