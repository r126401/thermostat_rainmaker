#include <stdio.h>
#include <stdbool.h>

#define N_ALARMS 4

typedef enum STATUS_ALARM_APP {

    ALARM_APP_ON,
    ALARM_APP_OFF
}STATUS_ALARM_APP;

typedef enum ALARM_APP {

    ALL_ALARMS,
    NO_ALARMS,
    WIFI_ALARM,
    MQTT_ALARM,
    NTP_ALARM,
    SENSOR_ALARM
}ALARM_APP;

void init_alarms();

void set_alarm(ALARM_APP alarm, STATUS_ALARM_APP status);

void clear_all_alarms();

bool get_status_alarm(ALARM_APP alarm);

uint8_t get_active_alarms();

