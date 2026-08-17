// Standard headers
#include <time.h>
// FreeRTOS headers
//
// ESP-IDF headers
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_netif_sntp.h"
#include "protocol_examples_common.h"
#include "esp_wifi.h"
#include "esp_sntp.h"
// ESP-IDF Component headers
//
// Custom headers
#include "global.h"
#include "wifi_setup.h"
#include "local_time.h"


esp_err_t wifi_init(void)
{
    // System initialization
	ESP_ERROR_CHECK(nvs_flash_init());
	ESP_ERROR_CHECK(esp_netif_init());
	ESP_ERROR_CHECK(esp_event_loop_create_default());

	// Establish Wi-Fi connection
	ESP_ERROR_CHECK(example_connect());

	// Print out Access Point Information
	wifi_ap_record_t ap_info;
	ESP_ERROR_CHECK(esp_wifi_sta_get_ap_info(&ap_info));
	ESP_LOGI(TAG, "--- Access Point Information ---");
	ESP_LOG_BUFFER_HEX("MAC Address", ap_info.bssid, sizeof(ap_info.bssid));
	ESP_LOG_BUFFER_CHAR("SSID", ap_info.ssid, sizeof(ap_info.ssid));
	ESP_LOGI(TAG, "Primary Channel: %d", ap_info.primary);
	ESP_LOGI(TAG, "RSSI: %d", ap_info.rssi);

    return ESP_OK;
}

esp_err_t timesync_init(void)
{
    esp_sntp_config_t config =
        ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");

    ESP_ERROR_CHECK(esp_netif_sntp_init(&config));

    ESP_LOGI(TAG, "Waiting for NTP time synchronization...");

    esp_err_t err = esp_netif_sntp_sync_wait(pdMS_TO_TICKS(10000));

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "NTP synchronization failed: %s",
                 esp_err_to_name(err));
        return err;
    }

    struct tm now_tm = get_local_time_struct(time(NULL));

    ESP_LOGI(TAG, "Initial NTP sync : %02d:%02d", now_tm.tm_hour, now_tm.tm_min);
    ESP_LOGI(TAG, "NTP sync interval is %d s", esp_sntp_get_sync_interval()/1000);

    return ESP_OK;
}