#include <stdio.h>
#include <time.h>
#include <locale.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_sntp.h"

#include "driver/gpio.h"
#define STRIP_GPIO GPIO_NUM_2

#include "wifi_setup.h"

#include "global.h"
#include "led_task.h"
#include "clock_task.h"
#include "ntp.h"

void app_main()
{
    wifi_setup();

    // char buff[70] = { '\0' };
    // struct tm my_time =
    // {
    //     .tm_year = 126, // = year 2026
    //     .tm_mon = 8,
    //     .tm_mday = 6,
    //     .tm_hour = 22,
    //     .tm_min = 47,
    //     .tm_sec = 20
    // };

    // if (strftime(buff, sizeof buff, "%A %c", &my_time))
    //     puts(buff);
    // else
    //     puts("strftime failed");

    // setlocale(LC_TIME, "fr_FR.utf8");

    // if (strftime(buff, sizeof buff, "%A %c", &my_time))
    //     puts(buff);
    // else
    //     puts("strftime failed");






    // esp_sntp_setservername(0, "pool.ntp.org");
    // esp_sntp_init();

    // // Wait for time to be set
    // time_t now = 0;
    // struct tm timeinfo = {0};
    // int retry = 0;
    // const int retry_count = 10;

    // while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count) {
    //     ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
    //     vTaskDelay(10000 / portTICK_PERIOD_MS);
    // }

    // if (retry == retry_count) {
    //     ESP_LOGE(TAG, "Failed to synchronize time");
    //     return;
    // }

    // // Update 'now' variable with current time
    // time(&now);
    // localtime_r(&now, &timeinfo);

    // // Print the current time
    // ESP_LOGI(TAG, "Current time: %s", asctime(&timeinfo));


    ntp_sync();




    time_t now;
    char strftime_buf[64];
    struct tm timeinfo;

    time(&now);
    setenv("TZ", "Europe/Paris", 1);
    tzset();

    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);





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
