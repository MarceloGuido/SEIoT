#include <Arduino.h>
#include <TM1637Display.h>
#include "config.h"
#include "display.h"

// Instância do objeto TM1637
TM1637Display display(DISPLAY_CLK, DISPLAY_DIO);

// Definição dos segmentos para a letra 'C' (Celsius) e 'U' (Umidade)
const uint8_t U_SYM = SEG_F | SEG_E | SEG_D | SEG_C | SEG_B;  // Representa 'U'
const uint8_t C_SYM = SEG_A | SEG_F | SEG_E | SEG_D;          // Representa 'C'

unsigned long ultimoTempoDisplay = 0;
bool mostrarTemperatura = true;

void iniciarDisplay()
{
    display.setBrightness(0x0f); // Brilho máximo (0x00 a 0x0f)
    display.clear();
}

void atualizarDisplay(float temperatura, float umidade)
{
    // Se a leitura do DHT11 estiver inválida, exibe "Err"
    if (isnan(temperatura) || isnan(umidade))
    {
        uint8_t errData[] = {
            SEG_A | SEG_F | SEG_E | SEG_D | SEG_G, // E
            SEG_E | SEG_G,                         // r
            SEG_E | SEG_G,                         // r
            0x00
        };
        display.setSegments(errData);
        return;
    }

    // Alterna a exibição a cada 3 segundos (3000 ms)
    if (millis() - ultimoTempoDisplay > 3000)
    {
        ultimoTempoDisplay = millis();
        mostrarTemperatura = !mostrarTemperatura;
    }

    if (mostrarTemperatura)
    {
        int tempInt = (int)temperatura;
        // Exibe o valor nos dois primeiros dígitos e 'C' no último pino
        display.showNumberDec(tempInt, false, 2, 0); 
        display.setSegments(&C_SYM, 1, 3);          
    }
    else
    {
        int umidInt = (int)umidade;
        // Exibe o valor nos dois primeiros dígitos e 'U' no último pino
        display.showNumberDec(umidInt, false, 2, 0); 
        display.setSegments(&U_SYM, 1, 3);          
    }
}
