#include <ESP8266mDNS.h>

#include "config.h"
#include "mdns.h"

void iniciarMDNS()
{
    if (MDNS.begin(HOSTNAME))
    {
        Serial.print("mDNS iniciado: http://");
        Serial.print(HOSTNAME);
        Serial.println(".local");
    }
    else
    {
        Serial.println("Erro ao iniciar mDNS");
    }

    // Publica o serviço HTTP
    MDNS.addService("http", "tcp", 80);
}

void atualizarMDNS()
{
    MDNS.update();
}
