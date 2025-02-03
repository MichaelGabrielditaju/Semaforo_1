#include "pico/stdlib.h"

// Função para atualizar os estados dos LEDs
void set_led_color(uint red_pin, uint yellow_pin, uint green_pin, bool R, bool Y, bool G) {
    gpio_put(red_pin, R);   // Configura o estado do LED vermelho
    gpio_put(yellow_pin, Y); // Configura o estado do LED amarelo
    gpio_put(green_pin, G);  // Configura o estado do LED verde
}

// Função de call-back do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    static int state = 0;
    const uint red_pin = 13;   // Pino para o LED vermelho
    const uint yellow_pin = 12; // Pino para o LED amarelo
    const uint green_pin = 11;  // Pino para o LED verde

    switch (state) {
        case 0: // Vermelho
            set_led_color(red_pin, yellow_pin, green_pin, true, false, false);
            state = 1;
            break;
        case 1: // Amarelo
            set_led_color(red_pin, yellow_pin, green_pin, false, true, false);
            state = 2;
            break;
        case 2: // Verde
            set_led_color(red_pin, yellow_pin, green_pin, false, false, true);
            state = 0;
            break;
    }
    return true;
}

int main() {
    // Configuração dos pinos GPIO
    const uint red_pin = 13;   // Pino para o LED vermelho
    const uint yellow_pin = 12; // Pino para o LED amarelo
    const uint green_pin = 11;  // Pino para o LED verde

    gpio_init(red_pin);
    gpio_init(yellow_pin);
    gpio_init(green_pin);

    gpio_set_dir(red_pin, GPIO_OUT);
    gpio_set_dir(yellow_pin, GPIO_OUT);
    gpio_set_dir(green_pin, GPIO_OUT);

    // Inicializa o temporizador
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal
    while (true) {
        printf("Sistema funcionando...\n"); // Imprime informação a cada segundo
        sleep_ms(1000); // Aguarda 1 segundo antes do próximo ciclo
    }

    return 0;
}