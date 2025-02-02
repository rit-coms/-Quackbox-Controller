/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"


#define BUTTON_PIN 12  

void app_main(void)
{
    int buttonState = 0;

    printf("Hello world!\n");

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),  // Pin 12
        .mode = GPIO_MODE_INPUT,               // Set as input
        .pull_up_en = GPIO_PULLUP_ENABLE,      // Enable pull-up resistor
        .pull_down_en = GPIO_PULLDOWN_DISABLE,// Disable pull-down
        .intr_type = GPIO_INTR_DISABLE         // No interrupt
    };
    gpio_config(&io_conf);

    while (1) {
        buttonState = gpio_get_level(BUTTON_PIN);

        printf("Button state: %d\n", buttonState);

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
