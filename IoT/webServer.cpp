#include <ESP8266WiFi.h>

#include "webserver.h"
#include "dht.h"
#include "html.h"

WiFiServer server(80);

String header;

void iniciarServidor()
{
    server.begin();

    Serial.println("Servidor Web iniciado");
}

void processarServidor()
{
    WiFiClient client = server.available();

    if (!client)
        return;

    Serial.println("Novo cliente.");

    String currentLine = "";

    while (client.connected())
    {
        if (client.available())
        {
            char c = client.read();

            header += c;

            if (c == '\n')
            {
                if (currentLine.length() == 0)
                {
                    // Resposta HTTP

                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println("Connection: close");
                    client.println();

                    // Página

                    client.println(
                        gerarPagina(
                            obterTemperatura(),
                            obterUmidade()
                        )
                    );

                    client.println();

                    break;
                }
                else
                {
                    currentLine = "";
                }
            }
            else if (c != '\r')
            {
                currentLine += c;
            }
        }
    }

    header = "";

    client.stop();

    Serial.println("Cliente desconectado.");
}
