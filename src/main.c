#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LIGHT1_GPIO GPIO_NUM_10
#define IN_GPIO GPIO_NUM_9
#define LIGHT2_GPIO GPIO_NUM_6
#define TAG "SWITCH_DEBUG"

void app_main(void)
{
    gpio_reset_pin(LIGHT1_GPIO);
    gpio_reset_pin(LIGHT2_GPIO);
    gpio_reset_pin(IN_GPIO); //clear pins

    gpio_set_direction(LIGHT1_GPIO, GPIO_MODE_OUTPUT); //provides power
    gpio_set_direction(LIGHT2_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(IN_GPIO, GPIO_MODE_INPUT); //acts like sensor


    gpio_set_level(LIGHT1_GPIO, 1); //Constant High
    gpio_set_level(LIGHT2_GPIO, 0);

    //SET pin 9 to be off by default.
    //have an if condition for when pin 9 receives power
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask =  1ULL << IN_GPIO,
        .intr_type = GPIO_INTR_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    gpio_config(&io_conf);


    while(1) { //keep doing
        //do every 30 seconds
        int count = 0 ;
        int input_state = gpio_get_level(IN_GPIO);
        if (input_state == 1) {
            ESP_LOGI(TAG, "Switch state changed:HIGH (off)" );
            gpio_set_level(LIGHT2_GPIO, 1);
            count++;
        }else {
            ESP_LOGI(TAG, "Switch state changed: LOW (pressed)");
            gpio_set_level(LIGHT2_GPIO, 0);
        }
        input_state = 0;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

