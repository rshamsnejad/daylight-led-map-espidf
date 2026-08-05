# Notes

## TODO

* WiFi
* NTP

## Skeleton

```
app_main()
 ├── led_init()
 ├── wifi_init()
 ├── sensor_init()
 ├── xTaskCreate(led_task)
 ├── xTaskCreate(sensor_task)
 └── xTaskCreate(network_task)
 ```