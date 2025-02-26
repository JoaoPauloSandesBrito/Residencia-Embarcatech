/*
 * Nome do Arquivo: projeto_hidroponico.c
 * Autor: João Paulo Sandes Brito
 * Data: 26/02/2025
 * Descrição: Sistema para monitoramento e controle de uma estufa hidropônica.
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include "hardware/adc.h" // Biblioteca para controle do ADC (Conversor Analógico-Digital).
#include "hardware/pwm.h" // Hardware de PWM

uint32_t last_time_lcd = 0;     // Armazena o último tempo
uint32_t interval_lcd = 100;   // Intervalo de 100 ms
uint32_t last_time_button = 0;  // Armazena o último tempo
uint32_t interval_button = 200; // Intervalo de 200 ms (até 5x por segundo)

bool cor = true;
bool USB_data = false;

int horario_ligar_luz = 17;
int horario_desligar_luz = 20;
int horario;

float nivel_minimo_agua;
float nivel_minimo_ph; // Pode ser minimo ou maximo dependendo da solucao
float intensidade_luz = 0.75;

// Definição dos pinos sensores
#define DHT_PIN 19               // GP19 para DHT22 (temperatura e humidade)
#define PH_SENSOR_PIN 26         // GP26 (ADC0) para sensor de pH
#define EC_SENSOR_PIN 27         // GP27 (ADC1) para sensot de CE
#define TRIGGER_PIN 14           // GP14 para HC-SR04 (trigger)
#define ECHO_PIN 13              // GP13 para HC-SR04 (echo)
#define PUMP_PIN 16              // GP16 para bomba de agua
#define FAN_PIN 18               // GP18 para cooler
#define PWM_LUZ_PIN 24           // GP22 para luz artificial
#define VALVULA_SUBSTRATO_PIN 23 // GP23 para valvula solenoide de substrato nutritivo

// Definições de pinos LCD
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Definições de pinos LED RGB
#define RED_PIN 13
#define GREEN_PIN 11
#define BLUE_PIN 12

// botão de interupção
#define button_A 5
#define button_B 6
#define button_JOY 22

// Protótipos de funções
void init_sensors();
float read_ph();
float read_ec();
void setup_gpio();
void set_led_color();
void send_data_to_USB();

void controlar_luz();
void controlar_bomba_agua();
void controlar_ph_solucao();

void read_dht22();
void read_water_level();
void control_actuators();
void init_wifi();

// Variáveis globais
float temperatura = 0.0;
float umidade = 0.0;
float ph_valor = 0.0;
float ce_valor = 0.0;
int nivel_agua = 0;

const uint16_t WRAP_PERIOD = 1024; // Valor máximo do contador - WRAP
const float PWM_DIVISER = 4.0;     // Divisor do clock para o PWM (frequência de PWM para aproximadamente, 50Hz)

ssd1306_t ssd; // Inicializa a estrutura do display
char str0[20]; // Buffer para armazenar o número convertido
char str1[20]; // Buffer para armazenar o número convertido
char str2[20]; // Buffer para armazenar o número convertido
char str3[20]; // Buffer para armazenar o número convertido
char str4[20]; // Buffer para armazenar o número convertido

// Configuração do LCD
void lcd_init()
{
    i2c_init(I2C_PORT, 400 * 1000); // I2C Initialisation. Using it at 400Khz.

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA);                     // Pull up the data line
    gpio_pull_up(I2C_SCL);                     // Pull up the clock line

    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd);                                         // Configura o display
    ssd1306_send_data(&ssd);                                      // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

void lcd_show()
{
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (current_time - last_time_lcd >= interval_lcd)
    {
        // Atualiza o conteúdo do display com animações
        ssd1306_fill(&ssd, !cor); // Limpa o display
        sprintf(str0, "Agua: %d", nivel_agua);
        sprintf(str1, "PH: %.2f", ph_valor);
        sprintf(str2, "Cond: %.2f", ce_valor);
        sprintf(str3, "Temp:  %d", temperatura);
        sprintf(str4, "Umidade: %.2f", umidade);

        ssd1306_draw_string(&ssd, str0, 16, 4);  // Desenha uma string 8
        ssd1306_draw_string(&ssd, str1, 16, 16); // Desenha uma string 28
        ssd1306_draw_string(&ssd, str2, 16, 28); // Desenha uma string 48
        ssd1306_draw_string(&ssd, str3, 16, 40); // Desenha uma string 28
        ssd1306_draw_string(&ssd, str4, 16, 52); // Desenha uma string 48
        ssd1306_send_data(&ssd);                 // Atualiza o display
        last_time_lcd = current_time;
    }
}

// Função para configurar o módulo PWM
void pwm_setup(int PORTA_GPIO)
{
    gpio_set_function(PORTA_GPIO, GPIO_FUNC_PWM);   // habilitar o pino GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(PORTA_GPIO); // obter o canal PWM da GPIO
    pwm_set_clkdiv(slice, PWM_DIVISER);             // define o divisor de clock do PWM
    pwm_set_wrap(slice, WRAP_PERIOD);               // definir o valor de wrap
    pwm_set_gpio_level(PORTA_GPIO, 0);              // definir o cico de trabalho (duty cycle) do pwm
    pwm_set_enabled(slice, true);                   // habilita o pwm no slice correspondente
}

void set_duty_cycle(int PORTA_GPIO, float duty_cycle)
{
    int duty_cicle_num = WRAP_PERIOD * duty_cycle;
    pwm_set_gpio_level(PORTA_GPIO, duty_cicle_num); // definir o cico de trabalho (duty cycle) do pwm
}

void init_sensors()
{
    adc_init();
    adc_gpio_init(PH_SENSOR_PIN); // Configura o pino GP26 como entrada analógica
    adc_gpio_init(EC_SENSOR_PIN); // Configura o pino GP27 como entrada analógica
}

float read_ph()
{
    adc_select_input(0);                       // Seleciona o canal 0 (ADC0) para leitura.
    uint16_t valor_adc_0 = adc_read();         // Lê o valor do ADC no canal
    float tensao = valor_adc_0 * (3.3 / 4095); // Converte o valor ADC para tensao
    return tensao;
}

float read_ec()
{
    adc_select_input(1);                       // Seleciona o canal 0 (ADC0) para leitura.
    uint16_t valor_adc_1 = adc_read();         // Lê o valor do ADC no canal
    float tensao = valor_adc_1 * (3.3 / 4095); // Converte o valor ADC para tensao
    return tensao;
}

void setup_gpio(uint gpio_pin)
{
    // Configura o pino GPIO como saída
    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_OUT);
}

void set_led_color(uint red, uint green, uint blue)
{
    // Define o estado dos LEDs
    gpio_put(RED_PIN, red);     // Red LED
    gpio_put(GREEN_PIN, green); // Green LED
    gpio_put(BLUE_PIN, blue);   // Blue LED
}

void led_ok()
{
    set_led_color(0, 1, 0);
}

void led_erro()
{
    set_led_color(1, 0, 0);
}

void send_data_to_USB()
{
    printf("\nDados Sensores!\n");
    printf("temperatura: %.2f\n", temperatura);
    printf("umidade: %.2f\n", umidade);
    printf("ph_valor: %.2f\n", ph_valor);
    printf("ce_valor: %.2f\n", ce_valor);
    printf("nivel_agua: %d\n", nivel_agua);
}

void controlar_luz()
{
    if (horario == horario_ligar_luz)
        set_duty_cycle(PWM_LUZ_PIN, intensidade_luz);
    if (horario == horario_desligar_luz)
        set_duty_cycle(PWM_LUZ_PIN, 0);
}

void controlar_bomba_agua()
{
    if (nivel_agua < nivel_minimo_agua)
        gpio_put(PUMP_PIN, 1); // Liga a bomba de agua
    else
        gpio_put(PUMP_PIN, 0); // Desliga a bomba de agua
}

void controlar_ph_solucao()
{
    if (read_ph() < nivel_minimo_ph)
        gpio_put(VALVULA_SUBSTRATO_PIN, 1); // Libera o substrato
    else
        gpio_put(VALVULA_SUBSTRATO_PIN, 0); // Trava o substrato
}

void read_water_level()
{
    nivel_agua = 0; // Valor da leitura do Ultrassom
}

static void gpio_irq_handler(uint gpio, uint32_t events)
{

    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if (current_time - last_time_button >= interval_button)
    {
        if (gpio == button_A)
        {
            USB_data = !USB_data;
            printf("Transferencia USB ativada\n");
        }

        last_time_button = current_time;
    }
}

bool repeating_timer_callback(struct repeating_timer *t)
{
    ph_valor = read_ph();
    ce_valor = read_ec();

    if (USB_data)
        send_data_to_USB();

    return true;
}

int main()
{
    stdio_init_all();

    lcd_init();
    init_sensors();

    setup_gpio(RED_PIN);
    setup_gpio(GREEN_PIN);
    setup_gpio(BLUE_PIN);
    led_ok();

    pwm_setup(PWM_LUZ_PIN);
    setup_gpio(PUMP_PIN);
    setup_gpio(VALVULA_SUBSTRATO_PIN);

    struct repeating_timer timer;
    add_repeating_timer_ms(5000, repeating_timer_callback, NULL, &timer);

    // inicializar o botão de interrupção - GPIO5
    gpio_init(button_A);
    gpio_set_dir(button_A, GPIO_IN);
    gpio_pull_up(button_A);
    // inicializar o botão de interrupção - GPIO5
    gpio_init(button_B);
    gpio_set_dir(button_B, GPIO_IN);
    gpio_pull_up(button_B);
    // ativa a interrupção
    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(button_B, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);

    while (true)
    {
        controlar_luz();
        controlar_ph_solucao();
        controlar_bomba_agua();
        lcd_show();
    }
}