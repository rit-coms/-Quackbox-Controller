#include <stdio.h>
#include "esp_log.h"
#include "driver/i2s_std.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define I2S_PORT I2S_NUM_0

// I2S configuration
static i2s_chan_handle_t i2s_tx_chan;

void init_i2s() {
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_PORT, I2S_ROLE_MASTER);
    i2s_new_channel(&chan_cfg, &i2s_tx_chan, NULL);

    i2s_std_config_t std_cfg = {
        .clk_cfg  = I2S_STD_CLK_DEFAULT_CONFIG(44100), // 44.1kHz sample rate
        .slot_cfg = I2S_STD_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .bclk = GPIO_NUM_4,
            .ws   = GPIO_NUM_5,
            .dout = GPIO_NUM_6,
            .din  = I2S_GPIO_UNUSED
        },
    };

    i2s_channel_init_std_mode(i2s_tx_chan, &std_cfg);
    i2s_channel_enable(i2s_tx_chan);
}

// Function to play a simple audio buffer (test sound)
void play_audio() {
    uint16_t sample = 0;
    uint8_t buffer[1024];

    while (1) {
        for (int i = 0; i < sizeof(buffer) / 2; i++) {
            buffer[i * 2] = sample & 0xFF;
            buffer[i * 2 + 1] = (sample >> 8) & 0xFF;
            sample += 100;  // Generates a simple waveform
        }
        size_t bytes_written;
        i2s_channel_write(i2s_tx_chan, buffer, sizeof(buffer), &bytes_written, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main() {
    init_i2s();
    play_audio();
}

