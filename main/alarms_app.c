

#include "alarms_app.h"
#include "esp_log.h"
#include "events_app.h"

static char* TAG = "alarmas.c";


bool alarms[N_ALARMS];

static char* alarm2mnemonic(ALARM_APP alarm) {

    static char mnemonic[13] = {0};

    switch (alarm) {

        case ALL_ALARMS:
            strncpy(mnemonic,"ALL_ALARMS", 13 );
        break;
        case NO_ALARMS:
            strncpy(mnemonic,"NO_ALARMS", 13 );
        break;
        case WIFI_ALARM:
            strncpy(mnemonic,"WIFI_ALARM", 13 );
        break;
        case MQTT_ALARM:
            strncpy(mnemonic,"MQTT_ALARM", 13 );
        break;
        case NTP_ALARM:
            strncpy(mnemonic,"NTP_ALARM", 13 );
        break;
        case SENSOR_ALARM:
            strncpy(mnemonic,"SENSOR_ALARM", 13 );
        break;

    }
    return mnemonic;
}

void init_alarms() {

    int i;
    for (i=0;i<N_ALARMS;i++) {
        alarms[i] = true;
    }

}


void set_alarm(ALARM_APP alarm, STATUS_ALARM_APP status) {


    alarms[alarm] = status;
    event_app_t event_alarm;

    if (alarms[alarm] == status) {

        ESP_LOGW(TAG, "la alarma %s ya estaba en %d y no ha cambiado", alarm2mnemonic(alarm), status );
        return;
    }



    if (status == ALARM_APP_ON) {
        event_alarm.event_app = EVENT_APP_ALARM_ON;
    }

    if (get_active_alarms() == 0) {
        event_alarm.event_app = EVENT_APP_ALARM_OFF;
    }
    event_alarm.value = alarm;
    send_event_app(event_alarm);




}

void clear_all_alarms() {

}

bool get_status_alarm(ALARM_APP alarm) {

    return alarms[alarm];
}

uint8_t get_active_alarms() {

    uint8_t nalarms = 0;
    int i;
    for (i=0;i<N_ALARMS;i++) {

        if (alarms[i] == true) nalarms++;

    }

    ESP_LOGI(TAG, "Encontradas %ud alarmas activas", nalarms);

    return nalarms;


}


