**Descrição**
Este projeto é um programa para o microcontrolador RP2040 que utiliza o conversor analógico-digital (ADC) e sinais PWM para controle de LEDs RGB. Também inclui uma interface de comunicação via I2C com um display OLED SSD1306 e suporte para botões de interrupção.

**Recursos Principais**
- Leitura de valores analógicos dos potenciômetros conectados aos pinos GPIO26 e GPIO27.
- Controle de LEDs RGB via PWM nos pinos GPIO11 (verde), GPIO12 (azul) e GPIO13 (vermelho).
- Exibição de informações em um display OLED SSD1306 via comunicação I2C.
- Manipulação de botões de interrupção nos GPIOs 5, 6 e 22.
- Monitoramento serial via USB CDC.

**Descrição do Projeto**
O joystick fornecerá valores analógicos correspondentes aos eixos X e Y, que serão utilizados para:

**Controle da Intensidade dos LEDs RGB**
- O LED Azul terá seu brilho ajustado conforme o valor do eixo Y. Quando o joystick estiver solto (posição central - valor 2048), o LED permanecerá apagado. À medida que o joystick for movido para cima (valores menores) ou para baixo (valores maiores), o LED aumentará seu brilho gradualmente, atingindo a intensidade máxima nos extremos (0 e 4095).
- O LED Vermelho seguirá o mesmo princípio, mas de acordo com o eixo X. Quando o joystick estiver solto (posição central - valor 2048), o LED estará apagado. Movendo o joystick para a esquerda (valores menores) ou para a direita (valores maiores), o LED aumentará de brilho, sendo mais intenso nos extremos (0 e 4095).
- Os LEDs serão controlados via PWM para permitir variação suave da intensidade luminosa.

**Exibição no Display SSD1306**
- Um quadrado de 8x8 pixels será exibido, inicialmente centralizado, e se moverá proporcionalmente aos valores capturados pelo joystick.

**Funcionalidades Adicionais dos Botões**
**Botão do Joystick (GPIO 22):**
- Alternar o estado do LED Verde a cada acionamento.
- Modificar a borda do display para indicar quando foi pressionado, alternando entre diferentes estilos de borda a cada novo acionamento.

**Botão A (GPIO 5):**
- Ativar ou desativar os LEDs PWM a cada acionamento.

**Requisitos do Projeto**
- Uso de interrupções: Todas as funcionalidades relacionadas aos botões devem ser implementadas utilizando rotinas de interrupção (IRQ).
- Debouncing: Implementação obrigatória do tratamento de bouncing dos botões via software.
- Utilização do Display 128x64: Demonstração do entendimento do funcionamento do display e do protocolo I2C.

**Componentes Utilizados**
- Placa de desenvolvimento BitDogLab (RP2040)
- LED RGB (pinos GPIO11, GPIO12 e GPIO13)
- Joystick (eixos X e Y nos pinos GPIO26 e GPIO27, botão no GPIO22)
- Botão A (pino GPIO5)
- Display OLED SSD1306 conectado via I2C (GPIO14 e GPIO15)

**Link video:** https://drive.google.com/file/d/16dH-Ma6F1Ksa1zfVIMD3w3WdWCyTh08g/view?usp=sharing