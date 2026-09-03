#include <Arduino.h>
#include <DHT.h>
#include "config.h"
#include "dht.h"

DHT sensor(DHT_PIN, DHT_TYPE);

float temperatura = NAN;
float umidade = NAN;

// Mutex para sincronização de leitura/escrita
SemaphoreHandle_t dhtMutex;

// Função da Task do FreeRTOS
void taskDHT(void *pvParameters)
{
    sensor.begin();
    
    for (;;)
    {
        float novaUmidade = sensor.readHumidity();
        float novaTemperatura = sensor.readTemperature();

        if (!isnan(novaUmidade) && !isnan(novaTemperatura))
        {
            // Solicita a chave do Mutex antes de alterar os dados compartilhados
            if (xSemaphoreTake(dhtMutex, portMAX_DELAY) == pdTRUE)
            {
                temperatura = novaTemperatura;
                umidade = novaUmidade;
                xSemaphoreGive(dhtMutex); // Libera o Mutex
            }
        }

        // Suspende a tarefa por 2 segundos liberando o processador
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void iniciarDHT()
{
    // Cria o Mutex de proteção
    dhtMutex = xSemaphoreCreateMutex();

    // Cria a tarefa no FreeRTOS (Nome, Tamanho da Stack, Parâmetro, Prioridade, Handle)
    xTaskCreate(taskDHT, "Task_DHT", 2048, NULL, 1, NULL);
    Serial.println("Task DHT11 iniciada com RTOS.");
}

// O loop interno atualizarDHT não é mais necessário
void atualizarDHT() {}

float obterTemperatura()
{
    float temp = NAN;
    if (xSemaphoreTake(dhtMutex, portMAX_DELAY) == pdTRUE)
    {
        temp = temperatura;
        xSemaphoreGive(dhtMutex);
    }
    return temp;
}

float obterUmidade()
{
    float umid = NAN;
    if (xSemaphoreTake(dhtMutex, portMAX_DELAY) == pdTRUE)
    {
        umid = umidade;
        xSemaphoreGive(dhtMutex);
    }
    return umid;
}
