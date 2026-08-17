// Standard headers
//
// FreeRTOS headers
#include "freertos/FreeRTOS.h"
// ESP-IDF headers
#include "esp_log.h"
#include "driver/gpio.h"
// ESP-IDF Component headers
//
// Custom headers
#include "global.h"
#include "led_task.h"
#include "clock_task.h"
#include "wifi_setup.h"
#include "local_time.h"

#define STRIP_GPIO GPIO_NUM_2

void app_main()
{
    wifi_init();
    sync_time();
    
    time_t utc_now;
    time(&utc_now);
    struct tm now_local_tm = get_local_time(utc_now);
    ESP_LOGI(TAG, "Current system time : %04d-%02d-%02d %02d:%02d:%02d", now_local_tm.tm_year + 1900, now_local_tm.tm_mon + 1, now_local_tm.tm_mday, now_local_tm.tm_hour, now_local_tm.tm_min, now_local_tm.tm_sec);

    led_strip_parameters_t* p_strip_parameters = malloc(sizeof(led_strip_parameters_t));
    *p_strip_parameters = (led_strip_parameters_t){
        .led_gpio = STRIP_GPIO
    };

    led_task_parameters_t* p_led_task_parameters = malloc(sizeof(led_task_parameters_t));
    *p_led_task_parameters = (led_task_parameters_t){
        .index = 0,
        .blink_time = 200,
        .red = 255,
        .green = 0,
        .blue = 255
    };

    led_task_init(p_strip_parameters);

    xTaskCreate(
        &led_task,      // task function
        "led_task", // task name
        2048,           // stack size in words
        p_led_task_parameters,  // pointer to parameters
        5,              // priority
        NULL);          // out pointer to task handle
    
    
    clock_task_init(NULL);

    xTaskCreate(
        &clock_task,      // task function
        "clock_task", // task name
        2048,           // stack size in words
        NULL,  // pointer to parameters
        5,              // priority
        NULL);          // out pointer to task handle

}
