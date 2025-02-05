#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Definição dos pinos do LED RGB
#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12
#define BTN_A_PIN 5

// Função para exibir a mensagem na tela
void ExibirMensagem(const char *mensagem[], int num_linhas) {
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);

    struct render_area frame_area = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };
    calculate_render_area_buffer_length(&frame_area);

     for (int i = 0; i < num_linhas; i++) {
        ssd1306_draw_string(ssd, 5, 12 + (i * 12), mensagem[i]);
    }
    render_on_display(ssd, &frame_area);
}

void SinalAberto() { 
    gpio_put(LED_R_PIN, 0); 
    gpio_put(LED_G_PIN, 1); 
    gpio_put(LED_B_PIN, 0); 
	ExibirMensagem((const char *[]){
        "SINAL ABERTO",
        "ATRAVESSAR COM",
        "CUIDADO"
    }, 3);;
} 
 
void SinalAtencao() { 
    gpio_put(LED_R_PIN, 1); 
    gpio_put(LED_G_PIN, 1); 
    gpio_put(LED_B_PIN, 0); 
	ExibirMensagem((const char *[]){
        "SINAL DE",
        "ATENCAO",
        "PREPARE-SE"
    }, 3);
} 
 
void SinalFechado() { 
    gpio_put(LED_R_PIN, 1); 
    gpio_put(LED_G_PIN, 0); 
    gpio_put(LED_B_PIN, 0); 
	ExibirMensagem((const char *[]){
        "SINAL FECHADO",
        "AGUARDE"
    }, 2);
} 

// Funcao para verificar se o botao foi pressionado
int A_state = 0;
int WaitWithRead(int timeMS){
    for(int i = 0; i < timeMS; i = i+100){
        A_state = !gpio_get(BTN_A_PIN);
        if(A_state == 1){
            return 1;
        }
        sleep_ms(100);
    }
    return 0;
}

int main()
{
    stdio_init_all();   // Inicializa os tipos stdio padrão presentes ligados ao binário

    // Inicialização dos pinos do LED RGB
    gpio_init(LED_R_PIN);
    gpio_init(LED_G_PIN);
    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);

    // INICIANDO BOTÄO
    gpio_init(BTN_A_PIN); 
    gpio_set_dir(BTN_A_PIN, GPIO_IN); 
    gpio_pull_up(BTN_A_PIN);

    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    while (true) { 
        SinalFechado(); 
        int A_state = WaitWithRead(8000); //espera com leitura do botäo
 
        if (A_state) { //ALGUEM APERTOU O BOTAO
            SinalAtencao(); 
            sleep_ms(2000); 
 
            SinalAberto(); 
            sleep_ms(8000); 
        } else { 
            SinalAtencao(); 
            sleep_ms(5000); 
 
            SinalAberto(); 
            sleep_ms(10000); 
        } 
    }

    return 0;
}
