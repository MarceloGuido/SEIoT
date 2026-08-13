#ifndef HTML_H
#define HTML_H

#include <Arduino.h>

String gerarPagina(
    String estado1,
    String estado2,
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

    html += ".button{";
    html += "padding:16px 40px;";
    html += "font-size:25px;";
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

    // D1

    html += "<h2>LED D1</h2>";

    html += "<p>Estado: ";
    html += estado1;
    html += "</p>";

    if (estado1 == "off")
    {
        html += "<p>";
        html += "<a href='/5/on'>";
        html += "<button class='button'>ON</button>";
        html += "</a>";
        html += "</p>";
    }
    else
    {
        html += "<p>";
        html += "<a href='/5/off'>";
        html += "<button class='button'>OFF</button>";
        html += "</a>";
        html += "</p>";
    }

    // D2

    html += "<h2>LED D2</h2>";

    html += "<p>Estado: ";
    html += estado2;
    html += "</p>";

    if (estado2 == "off")
    {
        html += "<p>";
        html += "<a href='/4/on'>";
        html += "<button class='button'>ON</button>";
        html += "</a>";
        html += "</p>";
    }
    else
    {
        html += "<p>";
        html += "<a href='/4/off'>";
        html += "<button class='button'>OFF</button>";
        html += "</a>";
        html += "</p>";
    }

    html += "</body>";
    html += "</html>";

    return html;
}

#endif