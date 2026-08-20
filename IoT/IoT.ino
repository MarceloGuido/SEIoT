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

    iniciarDHT();
    
    iniciarDisplay();

    iniciarServidor();
}

void loop()
{
    // Atualiza as variáveis internas do DHT11 (a cada 2 segundos)
    atualizarDHT();

    // Obtém as leituras atualizadas do dht.cpp para enviar ao Display
    float t = obterTemperatura();
    float u = obterUmidade();

    // Atualiza a exibição no TM1637
    atualizarDisplay(t, u);

    // Mantém serviços de rede ativos
    atualizarMDNS();

    processarServidor();
}
