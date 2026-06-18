#include <ESP8266WiFi.h>
#include "webserver.h"

WiFiServer server(80);

String header;

String EstadoD1 = "off";
String EstadoD2 = "off";

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void iniciarServidor()
{
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);

    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);

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

    currentTime = millis();
    previousTime = currentTime;

    while (client.connected() &&
           currentTime - previousTime <= timeoutTime)
    {
        currentTime = millis();

        if (client.available())
        {
            char c = client.read();

            Serial.write(c);

            header += c;

            if (c == '\n')
            {
                if (currentLine.length() == 0)
                {
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println("Connection: close");
                    client.println();

                    if (header.indexOf("GET /5/on") >= 0)
                    {
                        EstadoD1 = "on";
                        digitalWrite(D1, HIGH);
                    }
                    else if (header.indexOf("GET /5/off") >= 0)
                    {
                        EstadoD1 = "off";
                        digitalWrite(D1, LOW);
                    }
                    else if (header.indexOf("GET /4/on") >= 0)
                    {
                        EstadoD2 = "on";
                        digitalWrite(D2, HIGH);
                    }
                    else if (header.indexOf("GET /4/off") >= 0)
                    {
                        EstadoD2 = "off";
                        digitalWrite(D2, LOW);
                    }

                    client.println("<!DOCTYPE html><html>");
                    client.println("<head>");
                    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                    client.println("<style>");
                    client.println("html {font-family: Verdana; text-align:center;}");
                    client.println(".button {background-color:#000000;color:white;padding:16px 40px;font-size:30px;}");
                    client.println(".button2 {background-color:#273336;}");
                    client.println("</style>");
                    client.println("</head>");

                    client.println("<body>");
                    client.println("<h1>Servidor Web ESP8266</h1>");

                    client.println("<p>Estado D1: " + EstadoD1 + "</p>");

                    if (EstadoD1 == "off")
                        client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
                    else
                        client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");

                    client.println("<p>Estado D2: " + EstadoD2 + "</p>");

                    if (EstadoD2 == "off")
                        client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
                    else
                        client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");

                    client.println("</body>");
                    client.println("</html>");
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
