#include <stdint.h>
#include <stdbool.h>



typedef enum EVENT_TYPE_LCD {

    UPDATE_TIME,
    UPDATE_TEXT_MODE,
    UPDATE_LABEL_MODE,
    UPDATE_TEMPERATURE,
    UPDATE_WIFI_STATUS,
    UPDATE_BROKER_STATUS,
    UPDATE_HEATING,
    UPDATE_THRESHOLD_TEMPERATURE,
    UPDATE_SCHEDULE,
    UPDATE_ICON_ERRORS,
    UPDATE_TEXT_SCHEDULE,
    UPDATE_PERCENT,
    QR_CONFIRMED



}EVENT_TYPE_LCD;

typedef struct event_lcd_t {

    uint32_t par1;
    uint32_t par2;
    uint32_t par3;
    bool status;
    char* text;
    float value;
    EVENT_TYPE_LCD event_type;

}event_lcd_t;


void send_event(event_lcd_t event);
char* event2mnemonic(EVENT_TYPE_LCD type_lcd);
void receive_event(event_lcd_t event);
void wait_event_lcd();