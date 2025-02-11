# Controle de Servo Motor com PWM no Raspberry Pi Pico

Este projeto demonstra como controlar um servo motor utilizando o PWM (Pulse Width Modulation) no Raspberry Pi Pico. O código foi desenvolvido para ajustar a posição do servo motor, variando o ciclo de trabalho (duty cycle), que controla a posição do servo.

**Objetivo**

O código foi projetado para controlar um servo motor de 180 graus, variando o ciclo de trabalho do sinal PWM. A variação do ciclo de trabalho ajusta a posição do servo motor em intervalos, permitindo que o motor se mova entre os ângulos de 0º e 180º.

**Requisitos**
    -   Raspberry Pi Pico
    -   Servo motor conectado ao pino GPIO 22 (ou pino de sua preferência)
    -   Fonte de alimentação para o servo motor (pode ser a alimentação do Raspberry Pi Pico, se o servo suportar)
    -   Fios de conexão

**Descrição do Código**

- **Configuração do PWM:** O código usa a biblioteca PWM do Raspberry Pi Pico para gerar sinais PWM que controlam a posição do servo. A função pwm_setup() configura o pino GPIO 22 como um pino de PWM, define a frequência e o divisor de clock para 50Hz, e ajusta o valor de wrap para determinar a precisão do controle.

- **Controle do Servo:** O ciclo de trabalho (duty cycle) do PWM é ajustado para controlar a posição do servo. O código alterna entre diferentes valores de duty cycle para mover o servo entre os ângulos de 0º, 90º e 180º.

- **Movimento Suave:** O código também permite o movimento suave entre os ângulos de 0º e 180º, variando gradualmente o duty cycle, o que resulta em uma movimentação progressiva do servo.

**Como Funciona**

    Configuração do PWM: O pino GPIO 22 do Raspberry Pi Pico é configurado para enviar um sinal PWM ao servo motor.
    Alteração do Duty Cycle: A cada ciclo de 5 segundos, o duty cycle é alterado para posicionar o servo nos ângulos de 0º, 90º e 180º, além de permitir a movimentação contínua entre esses ângulos.
    Cálculo do Duty Cycle: O valor do duty cycle é calculado com base no wrap period e na frequência desejada para o servo, que é 50Hz.

**Instalação e Configuração**

    Conecte o servo motor ao pino GPIO 22 do Raspberry Pi Pico.
    Certifique-se de que a biblioteca pico-sdk está instalada e configurada corretamente no seu ambiente.
    Compile e carregue o código no Raspberry Pi Pico utilizando o ambiente de desenvolvimento apropriado (por exemplo, VSCode com a extensão do Pico).

**Como Usar**

    Compile o código e carregue no seu Raspberry Pi Pico.
    O servo motor irá se mover entre os ângulos de 0º, 90º e 180º, com um ciclo de 5 segundos em cada posição.
    Experimente ajustar o código para personalizar os ângulos e o tempo de movimento.

**Observações**

    O código utiliza valores de duty cycle pequenos para controlar a posição do servo motor. Esses valores podem ser ajustados para obter um controle mais fino sobre o movimento.
    O servo motor deve ser alimentado adequadamente. Se o servo exigir mais corrente do que o Raspberry Pi Pico pode fornecer, utilize uma fonte externa de alimentação.

**Contribuições**

Sinta-se à vontade para contribuir para este projeto. Você pode fazer um fork, enviar pull requests ou abrir issues para sugestões ou melhorias.

**Observacoes**

Ao realizar o experimento com o código deste exercício utilizando o LED RGB na GPIO 12, o discente observou que, ao variar o ciclo de trabalho (duty cycle), era possível ajustar o brilho do LED. No entanto, devido aos valores muito pequenos do ciclo de trabalho utilizados para o controle do servo motor, o LED pode não ter apresentado uma variação visível no brilho, aparecendo mais apagado ou com um brilho muito fraco. Isso ocorre porque os ciclos de trabalho utilizados no código são ajustados para a precisão necessária para o controle do servo, mas não são suficientes para provocar uma alteração perceptível no brilho do LED RGB.