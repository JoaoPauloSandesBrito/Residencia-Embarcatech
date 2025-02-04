Os requisitos para a realização desta atividade são:

1) O acionamento dos LEDs (sinais do semáforo) deve iniciar na cor vermelha, conforme orientação presente na Figura 1, alterando para amarela e, em seguida, verde.

2) O temporizador deve ser ajustado para um atraso de 3 segundos (3.000ms).

3) A mudança de estado dos LEDs deve ser implementa na função de call-back do temporizador, a exemplo da rotina trabalhada na aula síncrona - repeating_timer_callback().

4) A rotina principal, presente no interior da estrutura de repetição while, deve imprimir algum tipo de informação a cada segundo (1.000 ms) - a mensagem enviada pela porta serial fica a critério do discente.

5) Com o emprego da Ferramenta Educacional BitDogLab, faça um experimento com o código deste exercício utilizando o LED RGB – GPIOs 11, 12 e 13.