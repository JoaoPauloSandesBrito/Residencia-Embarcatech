**Projeto de Automação de Horta Hidropônica**

Este projeto implementa um sistema de monitoramento e controle para uma horta hidropônica utilizando a Raspberry Pi Pico W. O sistema coleta dados de sensores (temperatura, umidade, pH, condutividade elétrica e nível de água) e controla atuadores (bomba de água, luz artificial, ventilador e válvula de substrato) para manter as condições ideais de cultivo.

Funcionalidades

    Monitoramento de Sensores:

        Temperatura e umidade do ar (DHT22).

        Nível de pH da solução nutritiva.

        Condutividade elétrica (CE) da solução.

        Nível de água no reservatório (sensor ultrassônico HC-SR04).

    Controle de Atuadores:

        Bomba de água para manter o nível mínimo de água.

        Luz artificial para simular ciclos de iluminação.

        Ventilador para controle de temperatura.

        Válvula de substrato para ajuste do pH da solução.

    Interface de Usuário:

        Display OLED para exibição dos dados em tempo real.

        Botões para interação com o sistema.

        Comunicação USB para envio de dados.

    Automação:

        Controle automático dos atuadores com base nas leituras dos sensores.

        Temporização para ciclos de luz e irrigação.

Hardware Necessário

    Microcontrolador: Raspberry Pi Pico W.

    Sensores:

        DHT22 (temperatura e umidade).

        Sensor de pH.

        Sensor de condutividade elétrica (CE).

        Sensor ultrassônico HC-SR04 (nível de água).

    Atuadores:

        Bomba de água.

        Luzes LED.

        Ventilador.

        Válvula solenoide.

    Display: OLED SSD1306 (128x64 pixels, I2C).

    Botões: Para interação com o sistema.

    LED RGB: Para feedback visual.

Dependências

    Bibliotecas:

        pico/stdlib.h: Biblioteca padrão da Raspberry Pi Pico.

        hardware/adc.h: Para leitura de sensores analógicos.

        hardware/i2c.h: Para comunicação I2C com o display OLED.

        ssd1306.h e font.h: Para controle do display OLED.

        cyw43_arch.h: Para conexão Wi-Fi (opcional).

    Ferramentas:

        Compilador GCC para ARM (parte do SDK da Raspberry Pi Pico).

        CMake para gerenciamento de build.

Configuração do Ambiente

    Instale o SDK da Raspberry Pi Pico:

        Siga o guia oficial: Getting Started with Raspberry Pi Pico.

    Clone o Repositório:
    bash
    Copy

    git clone https://github.com/JoaoPauloSandesBrito/Residencia-Embarcatech/tree/main/projeto_hidroponia
    cd projeto_hidroponia

    Configure o Build:

        Crie uma pasta build e configure o projeto com CMake:
        bash
        Copy

        mkdir build
        cd build
        cmake ..

    Compile o Projeto:
    bash
    Copy

    make

    Carregue o Firmware na Pico:

        Conecte a Raspberry Pi Pico ao computador via USB.

        Copie o arquivo .uf2 gerado para a Pico:
        bash
        Copy

        cp projeto_hidroponico.uf2 /media/seu-usuario/RPI-RP2/

Uso

    Conecte o Hardware:

        Conecte os sensores e atuadores aos pinos GPIO conforme definido no código.

    Execute o Sistema:

        O sistema iniciará automaticamente após o carregamento do firmware.

        Os dados dos sensores serão exibidos no display OLED e enviados via USB (se habilitado).

    Interação:

        Use os botões para habilitar/desabilitar funcionalidades específicas.

        Ajuste os parâmetros de controle (ex.: horários de luz) diretamente no código.

Estrutura do Código

    main.c: Contém a função principal e o loop de controle.

    sensors.c/h: Funções para leitura dos sensores.

    actuators.c/h: Funções para controle dos atuadores.

    display.c/h: Funções para exibição no display OLED.

    communication.c/h: Funções para comunicação USB e Wi-Fi.

Exemplo de Saída

    Display OLED:
    Copy

    Agua: 0
    PH: 6.2
    Cond: 1.8
    Agua: 15
    Umidade: 60

    Saída USB:
    Copy

    Dados Sensores!
    temperatura: 25.50
    umidade: 60.00
    ph_valor: 6.20
    ce_valor: 1.80
    nivel_agua: 15

Melhorias Futuras

    Adicionar suporte para comunicação Wi-Fi (MQTT/HTTP).

    Implementar calibração automática dos sensores.

    Adicionar interface web para monitoramento remoto.

    Integrar IA para previsão de necessidades das plantas.


Contribuições são bem-vindas! Siga os passos abaixo:

    Faça um fork do projeto.

    Crie uma branch para sua feature (git checkout -b feature/nova-feature).

    Commit suas mudanças (git commit -m 'Adiciona nova feature').

    Push para a branch (git push origin feature/nova-feature).

    Abra um Pull Request.

Contato
    Autor: João Paulo Sandes Brito

Link video explicativo: https://drive.google.com/file/d/1innKxGTKw2D88Wlr5EO2p1B1HYkrYD-6/view?usp=sharing
