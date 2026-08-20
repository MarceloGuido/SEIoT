#ifndef HTML_H
#define HTML_H

#include <Arduino.h>

String gerarPagina(
    float temperatura,
    float umidade)
{
    String html;

    html += "<!DOCTYPE html>";
    html += "<html>";

    html += "<head>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";

    html += "<style>";

    html += "body{";
    html += "font-family:Verdana;";
    html += "text-align:center;";
    html += "margin:20px;";
    html += "}";

    html += ".sensor{";
    html += "font-size:22px;";
    html += "margin:20px;";
    html += "}";

    html += "</style>";

    html += "</head>";

    html += "<body>";

    html += "<h1>Servidor Web ESP8266</h1>";

    // DHT11

    html += "<h2>Temperatura e Umidade</h2>";

    if (isnan(temperatura) || isnan(umidade))
    {
        html += "<p class='sensor'>Erro na leitura do DHT11</p>";
    }
    else
    {
        html += "<p class='sensor'>";
        html += "Temperatura: ";
        html += String(temperatura, 1);
        html += " &deg;C";
        html += "</p>";

        html += "<p class='sensor'>";
        html += "Umidade: ";
        html += String(umidade, 1);
        html += " %";
        html += "</p>";
    }

    html += "</body>";
    html += "</html>";

    return html;
}

#endif
