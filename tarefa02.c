//Bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

//Defino os pinos GPIOs associados a cada função
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13
#define BUZZER 21

//Função que inicializa e configura os GPIOs
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

//Função que desliga todos os leds configurando os pinos para 0
void turn_off_leds() {
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 0);
}

//Função que vai interpretar os comandos recebidos
void handle_command(const char *command) {
    if (strcmp(command, "LED_GREEN") == 0) {
        turn_off_leds();
        gpio_put(LED_GREEN, 1);
    } else if (strcmp(command, "LED_BLUE") == 0) {
        turn_off_leds();
        gpio_put(LED_BLUE, 1);
    } else if (strcmp(command, "LED_RED") == 0) {
        turn_off_leds();
        gpio_put(LED_RED, 1);
    } else if (strcmp(command, "ALL_ON") == 0) {
        gpio_put(LED_GREEN, 1);
        gpio_put(LED_BLUE, 1);
        gpio_put(LED_RED, 1);
    } else if (strcmp(command, "ALL_OFF") == 0) {
        turn_off_leds();
    } else if (strcmp(command, "BUZZER") == 0) {
        gpio_put(BUZZER, 1);
        sleep_ms(2000);
        gpio_put(BUZZER, 0);
    } else {
        printf("Invalid command\n");
    }
}

//Função principal onde o comando será recebido pelo usuário
int main() {
    stdio_init_all();
    initialize_gpio();

    printf("Ready to receive commands\n");

    char command[32];
    while (true) {
        printf("Enter command: ");
        scanf("%31s", command);
        handle_command(command);
    }

    return 0;
}
