#include "pico/stdlib.h"
#include "pico/time.h" // Inclui a biblioteca para gerenciamento de tempo

#define LED_PIN_RED 13
#define LED_PIN_BLUE 12
#define LED_PIN_GREEN 11
#define button_PIN 5

bool red_status = false;
bool blue_status = false;
bool green_status = false;
bool button_status = true;

bool toggle_led_callback(alarm_id_t id, void *user_data);

// rotina da interrupção
static void gpio_irq_handler(uint gpio, uint32_t events)
{
    if (button_status)
    {
        red_status = true;
        blue_status = true;
        green_status = true;
        button_status = false;
        gpio_put(LED_PIN_RED, red_status);
        gpio_put(LED_PIN_BLUE, blue_status);
        gpio_put(LED_PIN_GREEN, green_status);

        add_alarm_in_ms(1000, toggle_led_callback, NULL, false);
    }
}

int main()
{
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    gpio_init(button_PIN);
    gpio_set_dir(button_PIN, GPIO_IN);
    gpio_pull_up(button_PIN);

    gpio_set_irq_enabled_with_callback(button_PIN, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);

    while (1)
    {
    }
}

bool toggle_led_callback(alarm_id_t id, void *user_data)
{
    if (red_status)
    {
        red_status = false;
        add_alarm_in_ms(1000, toggle_led_callback, NULL, false);
    }
    else if (blue_status)
    {
        blue_status = false;
        add_alarm_in_ms(1000, toggle_led_callback, NULL, false);
    }
    else if (green_status)
    {
        green_status = false;
        button_status = true;
    }

    gpio_put(LED_PIN_RED, red_status);
    gpio_put(LED_PIN_BLUE, blue_status);
    gpio_put(LED_PIN_GREEN, green_status);

    return false; // Retorna false para indicar que o alarme não deve ser repetido automaticamente
}