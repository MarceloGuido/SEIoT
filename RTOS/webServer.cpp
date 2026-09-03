#include <ESP8266WiFi.h>
#include "webserver.h"
#include "dht.h"
#include "html.h"

WiFiServer server(80);

void taskWebServer(void *pvParameters)
{
    server.begin();
    Serial.println("Servidor Web rodando em Task RTOS.");

    for (;;)
    {
        WiFiClient client = server.available();

        if (client)
        {
            String header = "";
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
                            client.println("HTTP/1.1 200 OK");
                            client.println("Content-type:text/html");
                            client.println("Connection: close");
                            client.println();

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
                vTaskDelay(1 / portTICK_PERIOD_MS); // Yield para a CPU
            }
            client.stop();
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void iniciarServidor()
{
    xTaskCreate(taskWebServer, "Task_WebServer", 4096, NULL, 2, NULL); // Prioridade mais alta
}

void processarServidor() {}
