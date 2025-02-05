🚦 Projeto: Sistema de Controle de Sinalização com Display OLED e LED RGB
Este projeto implementa um sistema de controle de sinalização usando a Raspberry Pi Pico. O sistema utiliza um display OLED SSD1306 para exibir mensagens de aviso e LED RGB para sinalização visual. Um botão permite interação com o sistema para simular a transição dos sinais de fechado, atenção e aberto.

🛠️ Funcionalidades
Display OLED SSD1306: Exibe mensagens relacionadas ao estado atual do sinal.
LED RGB: Muda de cor para indicar o estado atual:
🔴 Sinal Fechado (LED vermelho): Aguarde.
🟡 Sinal de Atenção (LED amarelo): Prepare-se.
🟢 Sinal Aberto (LED verde): Atravesse com cuidado.
Interação com Botão: O botão inicia a transição dos estados de sinalização.
🖥️ Hardware Utilizado
Raspberry Pi Pico
Display OLED SSD1306 (I2C)
LED RGB (3 pinos separados: vermelho, verde e azul)
Botão de entrada para interação
⚙️ Configuração dos Pinos
I2C (Display OLED)

SDA: GPIO 14
SCL: GPIO 15
LED RGB

Vermelho: GPIO 13
Verde: GPIO 11
Azul: GPIO 12
Botão de entrada: GPIO 5

📜 Descrição do Código
Inicialização:
Configura os pinos do LED RGB, do botão e do display OLED.

Funções de Sinalização:

SinalAberto(): Acende o LED verde e exibe a mensagem "SINAL ABERTO".
SinalAtencao(): Acende o LED amarelo e exibe "SINAL DE ATENÇÃO".
SinalFechado(): Acende o LED vermelho e exibe "SINAL FECHADO".
Verificação de Botão:
A função WaitWithRead() verifica se o botão foi pressionado durante um intervalo de tempo específico.

Loop Principal:
O código entra em um loop infinito que alterna entre os estados de sinalização baseado na interação com o botão.

🚀 Como Executar
Conecte todos os componentes conforme a configuração dos pinos.
Compile e carregue o código na Raspberry Pi Pico usando o ambiente de desenvolvimento adequado (ex.: VSCode com o SDK do Raspberry Pi Pico).
Alimente a Pico e observe o funcionamento do sistema de sinalização. Pressione o botão para iniciar a transição de estados.
📦 Dependências
Este projeto utiliza as seguintes bibliotecas:

pico/stdlib.h — Biblioteca padrão para Raspberry Pi Pico.
ssd1306.h — Biblioteca para controle do display OLED SSD1306.
hardware/i2c.h — Biblioteca para comunicação I2C.
📝 Licença
Este projeto é de código aberto. Você pode modificá-lo e distribuí-lo conforme desejar.
