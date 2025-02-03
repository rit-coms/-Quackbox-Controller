#include <stdio.h>
#include "freertos/FreeRTOS.h"

#include "driver/gpio.h"

#define OUT_PIN_1 GPIO_NUM_4
#define OUT_PIN_2 GPIO_NUM_5
#define OUT_PIN_3 GPIO_NUM_6
#define SENSE_PIN_1 GPIO_NUM_21
#define SENSE_PIN_2 GPIO_NUM_22
#define SENSE_PIN_3 GPIO_NUM_23

/// @brief Pin initializer that returns a gpio_config_t with interrupts disabled
/// and changes the pull down resistor depending on whether it's an input pin
/// @param pin_num GPIO pin number
/// @param sense boolean determining whether the pin is a sense pin or an output pin
/// @return a gpio_config_t struct used to initialize the settings for a gpio pin
gpio_config_t pin_init_config(int pin_num, bool sense) {
    return (gpio_config_t) {
        .pin_bit_mask = (1ULL << pin_num),
        .mode = (sense) ? GPIO_MODE_INPUT: GPIO_MODE_OUTPUT,
        .pull_down_en = (sense) ? 1 : 0,
        .pull_up_en = 0,
        .intr_type = GPIO_INTR_DISABLE
    };
}

/// @brief 
/// @param  
/// @return 
int app_main(void) {
    // Small delay to prevent immediate reboot issues
    vTaskDelay(pdMS_TO_TICKS(500));

    printf("Initializing Button Matrix...\n");

    gpio_num_t out_pins_num[] = {OUT_PIN_1, OUT_PIN_2, OUT_PIN_3};
    gpio_num_t sense_pins_num[] = {SENSE_PIN_1, SENSE_PIN_2, SENSE_PIN_3};

    const size_t out_pins_length = sizeof(out_pins_num) / sizeof(gpio_num_t);
    const size_t sense_pins_length = sizeof(sense_pins_num) / sizeof(gpio_num_t);

    printf("out pins: %d\nsense pins: %d\n", out_pins_length, sense_pins_length);

    // initializes output pins
    for (size_t i = 0; i < out_pins_length; i++) {
        gpio_config_t pin_config = pin_init_config(out_pins_num[i], false);
        gpio_config(&pin_config);
    }
    // initializes input pins
    for (size_t i = 0; i < sense_pins_length; i++) {
        gpio_config_t pin_config = pin_init_config(sense_pins_num[i], true);
        gpio_config(&pin_config);
    }

    bool button_matrix[out_pins_length][sense_pins_length];
    vTaskDelay(pdMS_TO_TICKS(2000));

    while(true) {
        // clears the previous console output
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

        // iterate over all out pins
        for (size_t i = 0; i < out_pins_length; i++) {
            gpio_num_t out_pin_num = out_pins_num[i];
            gpio_set_level(out_pin_num, 1);
            // iterate over all sense pins
            for (size_t j = 0; j < sense_pins_length; j++) {
                gpio_num_t sense_pin_num = sense_pins_num[j];
                button_matrix[i][j] = gpio_get_level(sense_pin_num);
            }
            gpio_set_level(out_pin_num, 0);
        }

        // prints button matrix to console
        for (size_t i = 0; i < out_pins_length; i++) {
            for (size_t j = 0; j < sense_pins_length; j++) {
                bool button_enabled = button_matrix[i][j];
                printf("%d\t", button_enabled);
            }
            printf("\n");
        }

        fflush(stdout);

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}