#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h" // Inclui a biblioteca para gerenciamento de tempo, como manipulação de temporizadores e atrasos.

#define LED_PIN_RED 13
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 11

// Estados iniciais dos LEDs
bool red_status = true;
bool yellow_status = false;
bool green_status = false;

uint32_t last_time = 0;   // Armazena o tempo da última verificação
uint32_t interval = 1000; // Intervalo de 1 segundo para a saída no terminal

// Callback do temporizador que alterna os LEDs
bool repeating_timer_callback(struct repeating_timer *t)
{

    if (red_status)
    {
        red_status = !red_status;
        yellow_status = true;
    }
    else if (yellow_status)
    {
        yellow_status = false;
        green_status = true;
    }
    else if (green_status)
    {
        green_status = false;
        red_status = true;
    }

    // Atualiza os LEDs conforme os estados alterados
    gpio_put(LED_PIN_RED, red_status);
    gpio_put(LED_PIN_YELLOW, yellow_status);
    gpio_put(LED_PIN_GREEN, green_status);

    return true;
}

int main()
{
    stdio_init_all(); // Inicializa a comunicação serial

    // Configuração dos pinos dos LEDs como saída
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Define os estados iniciais dos LEDs
    gpio_put(LED_PIN_RED, red_status);
    gpio_put(LED_PIN_YELLOW, yellow_status);
    gpio_put(LED_PIN_GREEN, green_status);

    // Inicia um temporizador que chama a função a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (1)
    {
        uint32_t current_time = to_ms_since_boot(get_absolute_time());

        // Exibe "1 s" no terminal a cada segundo
        if (current_time - last_time >= interval)
        {
            printf("1 s");
            last_time = current_time;
        }
    }
}
