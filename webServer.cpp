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

void processarServidor()
{
    WiFiClient client = server.available();

    if(!client)
        return;

    while(client.connected())
    {
        if(client.available())
        {
            char c = client.read();

            header += c;

            if(c == '\n')
            {
                if(header.indexOf("GET /5/on") >= 0)
                    ligarD1();

                else if(header.indexOf("GET /5/off") >= 0)
                    desligarD1();

                else if(header.indexOf("GET /4/on") >= 0)
                    ligarD2();

                else if(header.indexOf("GET /4/off") >= 0)
                    desligarD2();

                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println();

                client.println(
                    gerarPagina(
                        estadoD1(),
                        estadoD2()
                    )
                );

                client.println();

                break;
            }
        }
    }

    header = "";

    client.stop();
}
