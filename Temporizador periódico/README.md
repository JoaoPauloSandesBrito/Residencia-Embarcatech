Controle de Semáforo com Raspberry Pi Pico

Descrição:  Este programa implementa o controle de um semáforo utilizando um Raspberry Pi Pico e LEDs conectados aos GPIOs 11 (verde), 12 (amarelo) e 13 (vermelho). O funcionamento do semáforo segue a sequência padrão: vermelho -> amarelo -> verde, com cada estado durando 3 segundos.

Requisitos:
-Placa Raspberry Pi Pico
-LEDs conectados aos GPIOs 11, 12 e 13
-Ferramenta BitDogLab para simulação
-Biblioteca pico/stdlib.h para manipulação de GPIOs
-Biblioteca pico/time.h para gerenciamento de temporização

Funcionamento:
-O programa inicia com o LED vermelho aceso.
-A cada 3 segundos, a cor muda para a seguinte na sequência (vermelho -> amarelo -> verde -> vermelho).
-A mudança de estado dos LEDs é gerenciada dentro da função repeating_timer_callback().
-A cada 1 segundo, uma mensagem é impressa no terminal via comunicação serial.

Configuração e Execução:
-Conecte os LEDs aos GPIOs conforme indicado:
    -Vermelho: GPIO 13
    -Amarelo: GPIO 12
    -Verde: GPIO 11
-Compile e carregue o código no Raspberry Pi Pico.
-Utilize um monitor serial (como o minicom ou PuTTY) para visualizar as mensagens impressas.
-Se desejar, utilize a ferramenta BitDogLab para simular o funcionamento do semáforo com um LED RGB.