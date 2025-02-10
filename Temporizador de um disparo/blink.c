#include "pico/stdlib.h"
#include "pico/time.h" // Inclui a biblioteca para gerenciamento de tempo

// Definição dos pinos para os LEDs e o botão
#define LED_PIN_RED 13
#define LED_PIN_BLUE 12
#define LED_PIN_GREEN 11
#define button_PIN 5

// Variáveis de estado para os LEDs e o botão
bool red_status = false;
bool blue_status = false;
bool green_status = false;
bool button_status = true;

// Declaração antecipada da função de callback
int64_t toggle_led_callback(alarm_id_t id, void *user_data);

// Rotina de interrupção acionada pelo botão
static void gpio_irq_handler(uint gpio, uint32_t events)
{
    if (button_status) // Verifica se o botão ainda não foi pressionado anteriormente
    {
        // Liga todos os LEDs
        red_status = true;
        blue_status = true;
        green_status = true;
        button_status = false; // Impede novas ativações até que os LEDs sejam desligados

        // Atualiza os estados dos LEDs
        gpio_put(LED_PIN_RED, red_status);
        gpio_put(LED_PIN_BLUE, blue_status);
        gpio_put(LED_PIN_GREEN, green_status);

        // Agenda o primeiro desligamento após 1 segundo
        add_alarm_in_ms(1000, toggle_led_callback, NULL, false);
    }
}

int main()
{
    // Inicializa os pinos dos LEDs como saída
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Inicializa o pino do botão como entrada com pull-up
    gpio_init(button_PIN);
    gpio_set_dir(button_PIN, GPIO_IN);
    gpio_pull_up(button_PIN);

    // Configura a interrupção para detectar borda de descida (botão pressionado)
    gpio_set_irq_enabled_with_callback(button_PIN, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);

    while (1)
    {
        // Loop infinito aguardando interrupções
    }
}

// Callback para desligar os LEDs um de cada vez em intervalos de 1 segundo
int64_t toggle_led_callback(alarm_id_t id, void *user_data)
{
    if (red_status) // Se o LED vermelho estiver ligado, desliga ele primeiro
    {
        red_status = false;
        gpio_put(LED_PIN_RED, red_status);
        add_alarm_in_ms(1000, toggle_led_callback, NULL, false); // Agenda o próximo desligamento
    }
    else if (blue_status) // Depois desliga o azul
    {
        blue_status = false;
        gpio_put(LED_PIN_BLUE, blue_status);
        add_alarm_in_ms(1000, toggle_led_callback, NULL, false);
    }
    else if (green_status) // Por fim, desliga o verde e reativa o botão
    {
        green_status = false;
        gpio_put(LED_PIN_GREEN, green_status);
        button_status = true; // Permite que o botão seja pressionado novamente
    }

    return 0; // Retorna 0 para indicar que o alarme não deve ser repetido automaticamente
}