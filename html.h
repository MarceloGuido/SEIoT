#ifndef HTML_H
#define HTML_H

#include <Arduino.h>

String gerarPagina(String estado1, String estado2)
{
    String html;

    html += "<!DOCTYPE html>";
    html += "<html>";

    html += "<head>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";

    html += "<style>";
    html += "body{font-family:Verdana;text-align:center;}";
    html += ".button{padding:16px 40px;font-size:30px;}";
    html += "</style>";

    html += "</head>";

    html += "<body>";

    html += "<h1>Servidor Web ESP8266</h1>";

    html += "<h2>D1</h2>";
    html += "<p>Estado: " + estado1 + "</p>";

    if(estado1 == "off")
        html += "<a href='/5/on'><button class='button'>ON</button></a>";
    else
        html += "<a href='/5/off'><button class='button'>OFF</button></a>";

    html += "<h2>D2</h2>";
    html += "<p>Estado: " + estado2 + "</p>";

    if(estado2 == "off")
        html += "<a href='/4/on'><button class='button'>ON</button></a>";
    else
        html += "<a href='/4/off'><button class='button'>OFF</button></a>";

    html += "</body>";
    html += "</html>";

    return html;
}

#endif
