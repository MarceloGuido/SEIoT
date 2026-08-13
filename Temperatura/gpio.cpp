#include <Arduino.h>

#include "gpio.h"

#define D1 5
#define D2 4

String estado_led_D1 = "off";
String estado_led_D2 = "off";

void iniciarGPIO()
{
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);

    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);

    estado_led_D1 = "off";
    estado_led_D2 = "off";
}

void ligarD1()
{
    digitalWrite(D1, HIGH);
    estado_led_D1 = "on";
}

void desligarD1()
{
    digitalWrite(D1, LOW);
    estado_led_D1 = "off";
}

void ligarD2()
{
    digitalWrite(D2, HIGH);
    estado_led_D2 = "on";
}

void desligarD2()
{
    digitalWrite(D2, LOW);
    estado_led_D2 = "off";
}

String estadoD1()
{
    return estado_led_D1;
}

String estadoD2()
{
    return estado_led_D2;
}