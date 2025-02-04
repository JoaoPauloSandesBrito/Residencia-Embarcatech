#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h" // Inclui a biblioteca para gerenciamento de tempo, como manipulação de temporizadores e atrasos.

#define LED_PIN_RED 13
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 11

bool red_status = true;
bool yellow_status = false;
bool green_status = false;

uint32_t last_time = 0;   // Armazena o último tempo
uint32_t interval = 1000; // Intervalo de 1000 ms (1x por segundo)

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

    gpio_put(LED_PIN_RED, red_status);
    gpio_put(LED_PIN_YELLOW, yellow_status);
    gpio_put(LED_PIN_GREEN, green_status);

    return true;
}

int main()
{
    stdio_init_all(); // Inicializa a comunicação serial
    
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    gpio_put(LED_PIN_RED, red_status);
    gpio_put(LED_PIN_YELLOW, yellow_status);
    gpio_put(LED_PIN_GREEN, green_status);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (1)
    {
        uint32_t current_time = to_ms_since_boot(get_absolute_time());

        // Verifica se o intervalo passou (1000 ms)
        if (current_time - last_time >= interval)
        {
            printf("1 s");
        }
    }
}
