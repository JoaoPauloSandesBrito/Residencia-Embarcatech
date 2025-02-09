# Projeto de Integração: Matriz de LEDs, Display OLED e Botões com Raspberry Pi Pico

Este projeto demonstra a integração de múltiplos periféricos utilizando o Raspberry Pi Pico. Nele, você encontrará:

- **Matriz de LEDs WS2812B**: Uma matriz de 25 LEDs que exibe números (de 0 a 9) através de frames de cores pré-definidos.
- **Display OLED SSD1306**: Um display conectado via I2C que apresenta mensagens e atualizações visuais.
- **Botões com Interrupção**: Dois botões que, ao serem pressionados, alteram o estado de LEDs individuais e atualizam mensagens no display.
- **LED RGB**: Um LED RGB cujo estado (vermelho, verde e azul) é alterado em função das interações com os botões.
- **Comunicação USB**: Leitura de caracteres via USB para atualização de mensagens exibidas no display.

---

## Funcionalidades

- **Exibição de Números na Matriz de LEDs**:  
  Ao receber um caractere via USB que corresponda a um dígito (de '0' a '9'), o código seleciona o frame correspondente e o envia para a matriz de LEDs usando a PIO (Programmable I/O) do Pico.

- **Atualização do Display OLED**:  
  A cada 1000 ms, o display é atualizado com:
  - Um retângulo desenhado.
  - Mensagens que indicam o estado dos LEDs verde e azul (por exemplo, "Verde ON/OFF" e "Azul ON/OFF").
  - Uma string que inclui um caractere recebido via USB.

- **Interrupção por Botões**:  
  Dois botões conectados aos pinos GPIO 5 e 6 são configurados com interrupção.  
  - **Botão A (GPIO 5)**: Alterna o estado do LED verde e atualiza a mensagem correspondente no OLED.  
  - **Botão B (GPIO 6)**: Alterna o estado do LED azul e atualiza a mensagem correspondente no OLED.

- **Controle do LED RGB**:  
  Os pinos associados aos componentes do LED RGB (vermelho, verde e azul) são atualizados conforme os estados alterados pelos botões.

---

## Requisitos de Hardware

- **Placa**: Raspberry Pi Pico (ou placa compatível).
- **Matriz de LEDs WS2812B**:
  - Quantidade: 25 LEDs.
  - Conexão: Pino de saída definido (`OUT_PIN`) no GPIO 7.
- **Display OLED SSD1306**:
  - Conexão via I2C:
    - SDA: GPIO 14
    - SCL: GPIO 15
  - Endereço I2C: `0x3C`
- **Botões**:
  - Botão A: Conectado ao GPIO 5.
  - Botão B: Conectado ao GPIO 6.
- **LED RGB**:
  - Vermelho: GPIO 13
  - Verde: GPIO 11
  - Azul: GPIO 12

Modificações feitas no projeto pio_matrix, baseado no trabalho de [Ricardo Prates] (https://github.com/rmprates84/pio_matrix)

Modificações feitas no projeto I2C_Display_Embarca, baseado no trabalho de [WILTON LACERDA SILVA] (https://github.com/wiltonlacerda/EmbarcaTechU4C6/tree/main/I2C_Display_Embarca)