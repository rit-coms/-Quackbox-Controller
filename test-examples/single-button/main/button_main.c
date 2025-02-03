// includes needed
#include <stdio.h>
#include "freertos/FreeRTOS.h" // this is just for the portTICK_PERIOD_MS and vTaskDelay I think

// gpio documentation: https://docs.espressif.com/projects/esp-idf/en/stable/esp32c6/api-reference/peripherals/gpio.html#api-reference-normal-gpio
#include "driver/gpio.h"

// pin constant definitions
const int GPIO_LOW_PIN = 2;
const int GPIO_INPUT_PIN = 3;

// wire 3.3v to resistor to (button & input pin) and button to ground

// app_main is the default top level main function I think
void app_main(void)
{
    // prints to monitor
    printf("Hello button!\n");
    // sets the LOW_PIN to pulldown (0v)
    gpio_set_pull_mode(GPIO_LOW_PIN, GPIO_PULLDOWN_ONLY);
    // sets the interrupt
    gpio_intr_enable(GPIO_INPUT_PIN);

    // runs forever
    while (true) {
        // prints whether the pin level is high or low
        // aka: if the button is pressed down 1, else 0
        printf("GPIO PIN 3 LEVEL: %d\n", !gpio_get_level(GPIO_INPUT_PIN));
        // this is some ascii escape-code nonsense that clears the previous line
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        // this just makes sure that the stdout is flushed, honestly is pretty optional here
        // more useful for when you restart the esp and want to make sure that all the logs
        // reach your computer before the controller restarts
        fflush(stdout);
        // this just pauses the loop for 100ms
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
