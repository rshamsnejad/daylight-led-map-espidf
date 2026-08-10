#include <time.h>
#include "esp_log.h"
#include "esp_netif_sntp.h"
#include "ntp.h"
#include "global.h"

esp_err_t ntp_sync(void)
{
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");

    ESP_ERROR_CHECK(esp_netif_sntp_init(&config));

    ESP_LOGI(TAG, "Synchronizing time...");

    esp_err_t err = esp_netif_sntp_sync_wait(pdMS_TO_TICKS(10000));

    if (err == ESP_OK) {
        time_t now;
        struct tm timeinfo;

        time(&now);
        localtime_r(&now, &timeinfo);

        ESP_LOGI(TAG, "Time synced:");
        ESP_LOGI(TAG, "%s", asctime(&timeinfo));
    }

    esp_netif_sntp_deinit();

    return err;
}