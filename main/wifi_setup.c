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
// ESP-IDF Component headers
//
// Custom headers
#include "global.h"
#include "wifi_setup.h"



void wifi_init(void)
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
}
void wifi_free(void)
{
	// Disconnect from Wi-Fi
	ESP_ERROR_CHECK(example_disconnect());
}

esp_err_t sync_time(void)
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

    time_t now;
    time(&now);

    ESP_LOGI(TAG, "Time synchronized: %s", ctime(&now));

    return ESP_OK;
}