#include "pico/stdlib.h"
#include "pico/time.h" // Gerenciamento de tempo
#include "hardware/irq.h" // Gerenciamento de interrupções
#include "hardware/pwm.h" // Hardware de PWM

#define PWM_SERVO 22 // Pino do Servo conectado a GPIO como PWM
const uint16_t WRAP_PERIOD = 65535; // Valor máximo do contador - WRAP
const float PWM_DIVISER = 38.16; // Divisor do clock para o PWM (frequência de PWM para aproximadamente, 50Hz)
const uint16_t SERVO_STEP = 200; // Passo de incremento/decremento para o duty cycle do LED
uint16_t servo_level = 200; // Nível inicial do pwm (duty cycle)

// Função para configurar o módulo PWM
void pwm_setup()
{
    gpio_set_function(PWM_SERVO, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(PWM_SERVO); //obter o canal PWM da GPIO
    pwm_set_clkdiv(slice, PWM_DIVISER); //define o divisor de clock do PWM
    pwm_set_wrap(slice, WRAP_PERIOD); //definir o valor de wrap
    pwm_set_gpio_level(PWM_SERVO, 0); //definir o cico de trabalho (duty cycle) do pwm
    pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente
}

void set_duty_cycle(float duty_cycle){
    int duty_cicle_num = WRAP_PERIOD * duty_cycle;
    pwm_set_gpio_level(PWM_SERVO, duty_cicle_num); //definir o cico de trabalho (duty cycle) do pwm
}



int main()
{
    stdio_init_all();    
    pwm_setup(); // Configura o PWM

    while (true) {

        set_duty_cycle(0.12);   // 2) (Duty Cycle) de 0,12% - 180º 5s
        sleep_ms(5000);

        set_duty_cycle(0.0735); // 3) (Duty Cycle) de % - 90º 5s
        sleep_ms(5000);

        set_duty_cycle(0.025);  // 4) (Duty Cycle) de 0,025%  - 0º 5s
        sleep_ms(5000);

        for(int i=0;i<380;i++){ // 5) entre os ângulos de 0 e 180 graus
            set_duty_cycle(0.025 + i*0.00025); // Ciclo ativo de ±5μs,com um atraso de ajuste de 10ms
            sleep_ms(10);
        }

        for(int i=0;i<380;i++){ // 5) entre os ângulos de 180 e 0 graus
            set_duty_cycle(0.12 - i*0.00025); // Ciclo ativo de ±5μs,com um atraso de ajuste de 10ms
            sleep_ms(10);
        }

    }
}
