


#include "esp_err.h"




typedef enum ESTADO_RELE {
    INDETERMINADO = -1,
    OFF = 0,
    ON = 1
}ESTADO_RELE;

typedef enum TIPO_ACCION_TERMOSTATO {
	NO_ACCIONAR_TERMOSTATO,
	ACCIONAR_TERMOSTATO,
   NINGUNA_ACCION
}TIPO_ACCION_TERMOSTATO;

typedef enum DEVICE_STATUS {

   DEVICE_OK,
   SENSOR_FAIL
} DEVICE_STATUS;




char* write_date();
void task_iotThermostat();
void init_ds18b20();
//esp_err_t reading_temperature();
esp_err_t read_temperature(float *temperature_metered);
esp_err_t reading_local_temperature();
TIPO_ACCION_TERMOSTATO thermostat_action(float current_temperature);
ESTADO_RELE get_status_relay();
enum ESTADO_RELE relay_operation(ESTADO_RELE op);
#define TRAZAR "%s:%s:%d-->"
#define INFOTRAZA write_date(-1), __func__, __LINE__

