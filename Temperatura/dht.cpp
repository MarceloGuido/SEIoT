#include <Arduino.h>
#include <DHT.h>

#include "config.h"
#include "dht.h"

DHT sensor(DHT_PIN, DHT_TYPE);

float temperatura = NAN;
float umidade = NAN;

unsigned long ultimaLeitura = 0;

const unsigned long intervaloLeitura = 2000;

void iniciarDHT()
{
    sensor.begin();

    Serial.println("Sensor DHT11 iniciado.");
}

void atualizarDHT()
{
    unsigned long agora = millis();

    if (agora - ultimaLeitura < intervaloLeitura)
        return;

    ultimaLeitura = agora;

    float novaUmidade = sensor.readHumidity();
    float novaTemperatura = sensor.readTemperature();

    if (isnan(novaUmidade) || isnan(novaTemperatura))
    {
        Serial.println("Erro ao ler o DHT11.");
        return;
    }

    umidade = novaUmidade;
    temperatura = novaTemperatura;

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");
}

float obterTemperatura()
{
    return temperatura;
}

float obterUmidade()
{
    return umidade;
}