Controle de LEDs com Pushbutton e Temporizador

Descrição:  Este programa para Raspberry Pi Pico implementa um controle de LEDs utilizando um pushbutton. Quando o usuário pressiona o botão, os três LEDs são ligados simultaneamente. Em seguida, um temporizador inicia a sequência de desligamento dos LEDs, apagando um de cada vez a cada 3 segundos.

Requisitos:
- Ao pressionar o botão, os três LEDs devem acender simultaneamente.
- O temporizador do alarme deve ser configurado com um atraso de 3 segundos (3.000 ms) para a transição entre os estados dos LEDs.
- A lógica de desligamento deve ser implementada em funções de callback do temporizador, seguindo a abordagem trabalhada em aula.
- O botão só pode ser acionado novamente após o desligamento completo de todos os LEDs, evitando interferências durante a temporização.
- O programa deve ser testado na Ferramenta Educacional BitDogLab com um LED RGB utilizando os GPIOs 11, 12 e 13.

Componentes Necessários:
- Raspberry Pi Pico
- 3 LEDs (vermelho, azul e verde)
- 3 resistores adequados para LEDs
- Pushbutton
- Resistência pull-up para o botão (caso necessário)
- Jumpers e protoboard

Conexões:
LED Vermelho - GPIO 13
LED Azul - GPIO 12
LED Verde - GPIO 11
Pushbutton - GPIO 5

Como Executar o Programa:
- Compile e envie o código para a Raspberry Pi Pico.
- Conecte os componentes conforme a tabela acima.
- Pressione o botão para iniciar a sequência de iluminação e desligamento dos LEDs.
- Observe o comportamento dos LEDs e verifique se a sequência ocorre conforme esperado.

Funcionamento:
- Quando o botão é pressionado, todos os LEDs são acesos ao mesmo tempo.
- Após 3 segundos, o LED vermelho é desligado.
- Após mais 3 segundos, o LED azul é desligado.
- Após mais 3 segundos, o LED verde é desligado e o botão pode ser pressionado novamente.

Observação: Durante o processo de temporização, o botão não pode iniciar um novo ciclo até que todos os LEDs estejam apagados, garantindo que a sequência ocorra corretamente.