#include <Arduino.h>
#include "gpio.h"

String d1 = "off";
String d2 = "off";

void iniciarGPIO()
{
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);

    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
}

void ligarD1()
{
    digitalWrite(D1, HIGH);
    d1 = "on";
}

void desligarD1()
{
    digitalWrite(D1, LOW);
    d1 = "off";
}

void ligarD2()
{
    digitalWrite(D2, HIGH);
    d2 = "on";
}

void desligarD2()
{
    digitalWrite(D2, LOW);
    d2 = "off";
}

String estadoD1()
{
    return d1;
}

String estadoD2()
{
    return d2;
}
