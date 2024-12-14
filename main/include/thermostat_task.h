


#include "esp_err.h"
#include "app_priv.h"


char* write_date();
void task_iotThermostat();
void init_ds18b20();
esp_err_t read_temperature(float *temperature_metered);
esp_err_t reading_local_temperature();
TIPO_ACCION_TERMOSTATO thermostat_action(float current_temperature);
#define TRAZAR "%s:%s:%d-->"
#define INFOTRAZA write_date(-1), __func__, __LINE__

