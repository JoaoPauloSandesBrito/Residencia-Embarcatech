// Includes
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include <stdio.h>
#include "hardware/adc.h"      // Biblioteca para controle do ADC (Conversor Analógico-Digital).
#include "hardware/pwm.h" // Hardware de PWM

// Definições de pinos
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define PWM_AZUL 12                // Pino do led Azul
#define PWM_VERMELHO 13            // Pino do led Vermelho
#define PWM_VERDE 11               // Pino do led Verde

const uint16_t WRAP_PERIOD = 1024; // Valor máximo do contador - WRAP
const float PWM_DIVISER = 4.0;    // Divisor do clock para o PWM (frequência de PWM para aproximadamente, 50Hz)
const uint16_t SERVO_STEP = 200;    // Passo de incremento/decremento para o duty cycle do LED
uint16_t servo_level = 200;         // Nível inicial do pwm (duty cycle)

// botão de interupção
const uint button_A = 5;
const uint button_B = 6;
const uint button_JOY = 22;

int PINO_POTENCIOMETRO_X = 26;
int PINO_POTENCIOMETRO_Y = 27;

// led RGB
#define RED_PIN 13
#define GREEN_PIN 11
#define BLUE_PIN 12

bool red_led_state = false;
bool green_led_state = false;
bool blue_led_state = false;

char caractere[12] = "Caractere ";
char msgVerde[12] = "# Verde OFF";
char msgAzul[12] = "# Azul OFF";

bool cor = true;

// variaveis de tempo
uint32_t last_time_lcd = 0;     // Armazena o último tempo
uint32_t last_time_button = 0;  // Armazena o último tempo
uint32_t interval_lcd = 1000;   // Intervalo de 1000 ms
uint32_t interval_button = 200; // Intervalo de 100 ms (5x por segundo)

// Função para configurar o módulo PWM
void pwm_setup(int PORTA_GPIO)
{
    gpio_set_function(PORTA_GPIO, GPIO_FUNC_PWM);   // habilitar o pino GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(PORTA_GPIO); // obter o canal PWM da GPIO
    pwm_set_clkdiv(slice, PWM_DIVISER);            // define o divisor de clock do PWM
    pwm_set_wrap(slice, WRAP_PERIOD);              // definir o valor de wrap
    pwm_set_gpio_level(PORTA_GPIO, 0);              // definir o cico de trabalho (duty cycle) do pwm
    pwm_set_enabled(slice, true);                  // habilita o pwm no slice correspondente
}

void set_duty_cycle(int PORTA_GPIO,float duty_cycle)
{
    int duty_cicle_num = WRAP_PERIOD * duty_cycle;
    pwm_set_gpio_level(PORTA_GPIO, duty_cicle_num); // definir o cico de trabalho (duty cycle) do pwm
}

void set_led_color(uint red, uint green, uint blue)
{
    // Define o estado dos LEDs
    gpio_put(RED_PIN, red);     // Red LED
    gpio_put(GREEN_PIN, green); // Green LED
    gpio_put(BLUE_PIN, blue);   // Blue LED
}

void setup_gpio(uint gpio_pin)
{
    // Configura o pino GPIO como saída
    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_OUT);
}


static void gpio_irq_handler(uint gpio, uint32_t events)
{

    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if (current_time - last_time_button >= interval_button)
    {
        if (gpio == button_JOY)
        {
            green_led_state = !green_led_state;
            printf("Botao JOYSTICK pressionado");
        }

        if (gpio == button_A)
        {
            blue_led_state = !blue_led_state;
            red_led_state = !red_led_state;
            printf("Botao A pressionado");
        }

        set_led_color(red_led_state, green_led_state, blue_led_state);
        last_time_button = current_time;
    }
}

// função principal
int main()
{
    setup_gpio(RED_PIN);
    setup_gpio(GREEN_PIN);
    setup_gpio(BLUE_PIN);

    pwm_setup(PWM_AZUL);
    pwm_setup(PWM_VERMELHO);
    pwm_setup(PWM_VERDE);

    adc_init();
    adc_gpio_init(PINO_POTENCIOMETRO_X); // Configura o pino GP26 como entrada analógica
    adc_gpio_init(PINO_POTENCIOMETRO_Y); // Configura o pino GP27 como entrada analógica

    stdio_init_all(); // Inicializa comunicação USB CDC para monitor serial
    printf("iniciando a transmissão");

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA);                                        // Pull up the data line
    gpio_pull_up(I2C_SCL);                                        // Pull up the clock line
    ssd1306_t ssd;                                                // Inicializa a estrutura do display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd);                                         // Configura o display
    ssd1306_send_data(&ssd);                                      // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    // inicializar o botão de interrupção - GPIO5
    gpio_init(button_A);
    gpio_set_dir(button_A, GPIO_IN);
    gpio_pull_up(button_A);

    // inicializar o botão de interrupção - GPIO5
    gpio_init(button_B);
    gpio_set_dir(button_B, GPIO_IN);
    gpio_pull_up(button_B);

    // inicializar o botão de interrupção - GPI22
    gpio_init(button_JOY);
    gpio_set_dir(button_JOY, GPIO_IN);
    gpio_pull_up(button_JOY);

    // interrupção da gpio habilitada
    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(button_B, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(button_JOY, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);

    while (true)
    {
        uint32_t current_time = to_ms_since_boot(get_absolute_time());

        //leitura adc
        adc_select_input(0); // Seleciona o canal 0 (ADC0) para leitura.
        uint16_t valor_adc_y = adc_read(); // Lê o valor do ADC no canal
        float porcentagem_y = valor_adc_y * (1.00 / 4095); // Converte o valor ADC para

        adc_select_input(1); // Seleciona o canal 0 (ADC0) para leitura.
        uint16_t valor_adc_x = adc_read(); // Lê o valor do ADC no canal
        float porcentagem_x = valor_adc_x * (1.00 / 4095); // Converte o valor ADC para

        //mudar o ciclo de trabalho do led baseado no adc
        double potencia_azul= 2*(0.5-porcentagem_y) ;
        double potencia_vermelha= 2*(0.5-porcentagem_x) ;
        
        if(potencia_azul<0)potencia_azul=potencia_azul*-1;
        if(potencia_vermelha<0)potencia_vermelha=potencia_vermelha*-1;

        if(red_led_state) set_duty_cycle(PWM_VERMELHO,potencia_vermelha);
        else set_duty_cycle(PWM_VERMELHO,0);

        if(green_led_state) set_duty_cycle(PWM_VERDE,1.0);
        else set_duty_cycle(PWM_VERDE,0);

        if(blue_led_state) set_duty_cycle(PWM_AZUL,potencia_azul);
        else set_duty_cycle(PWM_AZUL,0);

        printf("Valor do ADC: %f %f\n", potencia_vermelha, potencia_azul);
        // Verifica se o intervalo passou e atualiza LCD
        if (current_time - last_time_lcd >= interval_lcd)
        {
            // Atualiza o conteúdo do display com animações
            ssd1306_fill(&ssd, !cor);                     // Limpa o display
            ssd1306_rect(&ssd, 3, 3, 122, 58, green_led_state, !green_led_state); // Desenha um retângulo
            //ssd1306_draw_string(&ssd, msgVerde, 16, 8);   // Desenha uma string
            //ssd1306_draw_string(&ssd, msgAzul, 16, 28);   // Desenha uma string
            //ssd1306_draw_string(&ssd, caractere, 16, 48); // Desenha uma string
            ssd1306_draw_string(&ssd, "#", 4+114*porcentagem_x, 4+48*(1-porcentagem_y));   // Desenha uma string
            ssd1306_send_data(&ssd);                      // Atualiza o display
            last_time_lcd = current_time;
        }
    }
}