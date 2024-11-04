


#include "esp_err.h"
#include "app_priv.h"


char* write_date();
void task_iotThermostat(void *args);
void init_ds18b20();
esp_err_t read_temperature(float *temperature_metered);
esp_err_t reading_local_temperature(app_params *datosApp);
#define TRAZAR "%s:%s:%d-->"
#define INFOTRAZA write_date(), __func__, __LINE__

