// Bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include "pico/bootrom.h" // Para o comando de reboot

// Defino os pinos GPIOs associados a cada função
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13
#define BUZZER 21

// Função que inicializa e configura os GPIOs
void initialize_gpio() {
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_init(BUZZER);

    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(BUZZER, GPIO_OUT);
}

// Função que desliga todos os LEDs
void turn_off_leds() {
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 0);
}

//função para acionar Led Azul  e desligar os demais 
void Lig_Led_Azul(){
    gpio_put(LED_BLUE,1);//liga o led azul 
    gpio_put(LED_RED,0);//desliga led vermelho
    gpio_put(LED_GREEN,0);//desliga led verde
}

// Função que exibe os comandos disponíveis
void print_help() {
    printf("\nComandos disponíveis:\n");
    printf("LED_GREEN  - Liga o LED verde\n");
    printf("LED_BLUE   - Liga o LED azul\n");
    printf("LED_RED    - Liga o LED vermelho\n");
    printf("ALL_ON     - Liga todos os LEDs (branco)\n");
    printf("ALL_OFF    - Desliga todos os LEDs\n");
    printf("BUZZER     - Aciona o buzzer por 2 segundos\n");
    printf("REBOOT     - Reinicia o microcontrolador\n");
    printf("DEMO       - Entra no modo de demonstração\n");
    printf("HELP       - Exibe esta lista de comandos\n\n");
}

// Função que interpreta os comandos recebidos
void handle_command(const char *command) {
    if (strcmp(command, "LED_GREEN") == 0) {
        turn_off_leds();
        gpio_put(LED_GREEN, 1);
        printf("LED verde ligado\n");
    } else if (strcmp(command, "LED_BLUE") == 0) {
        turn_off_leds();
        gpio_put(LED_BLUE, 1);
        printf("LED azul ligado\n");
    } else if (strcmp(command, "LED_RED") == 0) {
        turn_off_leds();
        gpio_put(LED_RED, 1);
        printf("LED vermelho ligado\n");
    } else if (strcmp(command, "ALL_ON") == 0) {
        gpio_put(LED_GREEN, 1);
        gpio_put(LED_BLUE, 1);
        gpio_put(LED_RED, 1);
        printf("Todos os LEDs ligados (branco)\n");
    } else if (strcmp(command, "ALL_OFF") == 0) {
        turn_off_leds();
        printf("Todos os LEDs desligados\n");
    } else if (strcmp(command, "BUZZER") == 0) {
        gpio_put(BUZZER, 1);
        printf("Buzzer ativado por 2 segundos\n");
        sleep_ms(2000);
        gpio_put(BUZZER, 0);
        printf("Buzzer desativado\n");
    } else if (strcmp(command, "REBOOT") == 0) {
        printf("Reiniciando o microcontrolador...\n");
        reset_usb_boot(0, 0); // Reinicia o microcontrolador
    } else if (strcmp(command, "DEMO") == 0) {
        printf("Modo de demonstração ativado. Pressione Ctrl+C para encerrar.\n");
        while (true) {
            // Alterna os LEDs
            gpio_put(LED_GREEN, 1);
            sleep_ms(500); // 500 ms
            gpio_put(LED_GREEN, 0);

            gpio_put(LED_BLUE, 1);
            sleep_ms(500); // 500 ms
            gpio_put(LED_BLUE, 0);

            gpio_put(LED_RED, 1);
            sleep_ms(500); // 500 ms
            gpio_put(LED_RED, 0);

            // Ativa o buzzer intermitentemente
            gpio_put(BUZZER, 1);
            sleep_ms(200); // 200 ms
            gpio_put(BUZZER, 0);
            sleep_ms(300); // 300 ms

            // Verifica se um novo comando foi recebido
            if (stdio_poll(0)) { // Verifica se há entrada disponível no terminal
                char new_command[32];
                scanf("%31s", new_command);
                if (strcmp(new_command, "DEMO") != 0) {
                    handle_command(new_command);
                    break;
                }
            }
        }
    } else if (strcmp(command, "HELP") == 0) {
        print_help();
    } else {
        printf("Comando inválido. Digite 'HELP' para ver os comandos disponíveis.\n");
    }
}

// Função principal onde o comando será recebido pelo usuário
int main() {
    stdio_init_all();
    initialize_gpio();

    printf("Sistema inicializado. Pronto para receber comandos.\n");
    print_help(); // Mostra os comandos logo no início

    char command[32];
    while (true) {
        printf("Digite um comando: ");
        scanf("%31s", command);
        handle_command(command);
    }

    return 0;
}

