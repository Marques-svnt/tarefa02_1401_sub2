#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include "pico/bootrom.h" // Para o comando de reboot
#include "hardware/pwm.h"
#include "hardware/clocks.h"

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

    // Configura o BUZZER para PWM
    gpio_set_function(BUZZER, GPIO_FUNC_PWM);

    // Encontra o slice PWM associado ao pino do buzzer
    uint slice_num = pwm_gpio_to_slice_num(BUZZER);

    // Configura o divisor de clock (maior divisor = menor frequência base)
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f); // Ajusta o divisor do clock
    pwm_init(slice_num, &config, true);

    // Inicializa o PWM com duty cycle 0
    pwm_set_gpio_level(BUZZER, 0);
}

// Função para configurar a frequência do buzzer
void set_buzzer_frequency(uint freq_hz) {
    if (freq_hz == 0) {
        // Desliga o buzzer
        pwm_set_gpio_level(BUZZER, 0);
        return;
    }

    // Encontra o slice PWM associado ao pino do buzzer
    uint slice_num = pwm_gpio_to_slice_num(BUZZER);

    // Calcula o divisor de clock para obter a frequência desejada
    uint32_t clock_freq = clock_get_hz(clk_sys);
    uint16_t wrap = clock_freq / (freq_hz * 4) - 1;

    pwm_set_wrap(slice_num, wrap);
    pwm_set_gpio_level(BUZZER, wrap / 2); // 50% duty cycle para som estável
}

// Função que desliga todos os LEDs
void turn_off_leds() {
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 0);
}

// Função que exibe os comandos disponíveis
void print_help() {
    printf("\nComandos disponíveis:\n");
    printf("LED_GREEN  - Liga o LED verde\n");
    printf("LED_BLUE   - Liga o LED azul\n");
    printf("LED_RED    - Liga o LED vermelho\n");
    printf("ALL_ON     - Liga todos os LEDs (branco)\n");
    printf("ALL_OFF    - Desliga todos os LEDs\n");
    printf("BUZZER     - Aciona o buzzer por 2 segundos (1 kHz)\n");
    printf("REBOOT     - Habilita o modo de gravação (USB bootloader)\n");
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
        printf("Buzzer ativado por 2 segundos (1 kHz)\n");
        set_buzzer_frequency(1000); // Define a frequência do buzzer para 1 kHz
        sleep_ms(2000);
        set_buzzer_frequency(0);   // Desliga o buzzer
        printf("Buzzer desativado\n");
    } else if (strcmp(command, "REBOOT") == 0) {
        printf("Habilitando o modo de gravação...\n");
        reset_usb_boot(0, 0); // Reinicia no modo USB bootloader
    } else if (strcmp(command, "DEMO") == 0) {
        printf("Modo de demonstração ativado. Pressione Ctrl+C para encerrar.\n");
        while (true) {
            gpio_put(LED_GREEN, 1);
            sleep_ms(500); 
            gpio_put(LED_GREEN, 0);

            gpio_put(LED_BLUE, 1);
            sleep_ms(500); 
            gpio_put(LED_BLUE, 0);

            gpio_put(LED_RED, 1);
            sleep_ms(500); 
            gpio_put(LED_RED, 0);

            set_buzzer_frequency(1000); 
            sleep_ms(200);
            set_buzzer_frequency(0);
            sleep_ms(300);
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
    print_help();

    char command[32];
    while (true) {
        printf("Digite um comando: ");
        scanf("%31s", command);
        handle_command(command);
    }

    return 0;
}