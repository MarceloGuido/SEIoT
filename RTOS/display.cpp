#include <Arduino.h>
#include <TM1637Display.h>
#include "config.h"
#include "display.h"
#include "dht.h"

TM1637Display display(DISPLAY_CLK, DISPLAY_DIO);

const uint8_t U_SYM = SEG_F | SEG_E | SEG_D | SEG_C | SEG_B;
const uint8_t C_SYM = SEG_A | SEG_F | SEG_E | SEG_D;

void taskDisplay(void *pvParameters)
{
    display.setBrightness(0x0f);
    display.clear();

    bool mostrarTemperatura = true;

    for (;;)
    {
        float t = obterTemperatura();
        float u = obterUmidade();

        if (isnan(t) || isnan(u))
        {
            uint8_t errData[] = {
                SEG_A | SEG_F | SEG_E | SEG_D | SEG_G,
                SEG_E | SEG_G,
                SEG_E | SEG_G,
                0x00
            };
            display.setSegments(errData);
        }
        else if (mostrarTemperatura)
        {
            display.showNumberDec((int)t, false, 2, 0); 
            display.setSegments(&C_SYM, 1, 3);          
        }
        else
        {
            display.showNumberDec((int)u, false, 2, 0); 
            display.setSegments(&U_SYM, 1, 3);          
        }

        mostrarTemperatura = !mostrarTemperatura;

        // Alterna a exibição a cada 3 segundos
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

void iniciarDisplay()
{
    xTaskCreate(taskDisplay, "Task_Display", 2048, NULL, 1, NULL);
}

// Função obsoleta no RTOS
void atualizarDisplay(float temperatura, float umidade) {}
