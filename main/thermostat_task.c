
#include "thermostat_task.h"


#include "esp_err.h"
#include "esp_log.h"
#include <string.h>
#include <math.h>
#include "time.h"
#include "onewire_bus.h"
#include "onewire_types.h"
#include "ds18b20.h"
#include <freertos/FreeRTOS.h>


static const char *TAG = "thermostat_task";

#define ONEWIRE_MAX_DS18B20 1
ds18b20_device_handle_t ds18b20s[ONEWIRE_MAX_DS18B20];

void init_ds18b20()
{

    

    // install 1-wire bus
    onewire_bus_handle_t bus = NULL;
    onewire_bus_config_t bus_config = {
        .bus_gpio_num = CONFIG_SENSOR_THERMOSTAT_GPIO,
    };
    onewire_bus_rmt_config_t rmt_config = {
        .max_rx_bytes = 10, // 1byte ROM command + 8byte ROM number + 1byte device command
    };
    ESP_ERROR_CHECK(onewire_new_bus_rmt(&bus_config, &rmt_config, &bus));

    int ds18b20_device_num = 0;
    //ds18b20_device_handle_t ds18b20s[ONEWIRE_MAX_DS18B20];
    onewire_device_iter_handle_t iter = NULL;
    onewire_device_t next_onewire_device;
    esp_err_t search_result = ESP_OK;

    // create 1-wire device iterator, which is used for device search
    ESP_ERROR_CHECK(onewire_new_device_iter(bus, &iter));
    ESP_LOGI(TAG, "Device iterator created, start searching...");
    do {
        search_result = onewire_device_iter_get_next(iter, &next_onewire_device);
        if (search_result == ESP_OK) { // found a new device, let's check if we can upgrade it to a DS18B20
            ds18b20_config_t ds_cfg = {};
            // check if the device is a DS18B20, if so, return the ds18b20 handle
            if (ds18b20_new_device(&next_onewire_device, &ds_cfg, &ds18b20s[ds18b20_device_num]) == ESP_OK) {
                ESP_LOGI(TAG, "Found a DS18B20[%d], address: %016llX", ds18b20_device_num, next_onewire_device.address);
                ds18b20_device_num++;
            } else {
                ESP_LOGI(TAG, "Found an unknown device, address: %016llX", next_onewire_device.address);
            }
        }
    } while (search_result != ESP_ERR_NOT_FOUND);
    ESP_ERROR_CHECK(onewire_del_device_iter(iter));
    ESP_LOGI(TAG, "Searching done, %d DS18B20 device(s) found", ds18b20_device_num);

    // Now you have the DS18B20 sensor handle, you can use it to read the temperature

}

esp_err_t read_temperature(float *temperature_metered) 

{
	esp_err_t error; 

	if (ds18b20_trigger_temperature_conversion(*ds18b20s) != ESP_OK) {
		ESP_LOGE(TAG, ""TRAZAR" Error al hacer la conversion de temperatura", INFOTRAZA);
		return ESP_FAIL;
	}
	if ((error = ds18b20_get_temperature(*ds18b20s, temperature_metered)) == ESP_OK) {

		//ESP_LOGI(TAG, "temperature read from DS18B20: %.2f", temperature_metered);	

	}


    return error;
    

}





char* write_date() {

	static char fecha_actual[120] = {0};

	time_t now;
	struct tm fecha;
	//ESP_LOGI(TAG, ""TRAZAR"ACTUALIZAR_HORA", INFOTRAZA);
    time(&now);
    localtime_r(&now, &fecha);


	sprintf(fecha_actual, "%02d/%02d/%04d %02d:%02d:%02d",
			fecha.tm_mday,
    		fecha.tm_mon + 1,
			fecha.tm_year + 1900,
			fecha.tm_hour,
			fecha.tm_min,
			fecha.tm_sec);

	return fecha_actual;

}

float redondear_temperatura(float temperatura) {

	float redondeado;
	float diferencia;
	float resultado = 0;
	float valor_absoluto;

	redondeado = lround(temperatura);
	diferencia = temperatura - redondeado;
	ESP_LOGE(TAG, "temperatura: %.2f, redondeado: %.2f, diferencia: %.2f", temperatura, redondeado, diferencia);
	if (diferencia == 0) {
		resultado = temperatura;
		ESP_LOGI(TAG, ""TRAZAR"TEMPERATURA ORIGINAL: %.2f, TEMPERATURA REDONDEADA: %.2f,", INFOTRAZA, temperatura, resultado);
		return resultado;

	}
	valor_absoluto = fabs(redondeado);
	ESP_LOGE(TAG, "temperatura: %.2f, redondeado: %.2f, diferencia: %.2f, valor absoluto :%.2f", temperatura, redondeado, diferencia, valor_absoluto);
	if (diferencia <= 0.25) {
		ESP_LOGI(TAG, "diferencia <= 0.25");
		resultado = valor_absoluto;
	}
	if ((diferencia > 0.25 ) && (diferencia < 0.5)) {
		ESP_LOGI(TAG, "((diferencia > 0.25 ) && (diferencia < 0.5))");
		resultado = valor_absoluto + 0.5;
	}

	if ((diferencia < -0.25)) {
		ESP_LOGI(TAG, "diferencia < -0.25");
		resultado = valor_absoluto - 0.5;
	}

	ESP_LOGI(TAG, ""TRAZAR"TEMPERATURA ORIGINAL: %.2f, TEMPERATURA REDONDEADA: %.2f,", INFOTRAZA, temperatura, resultado);
	return resultado;

}



esp_err_t reading_local_temperature(app_params *datosApp) {

    esp_err_t error = ESP_FAIL;
	float temperatura_a_redondear;
	float temperature;

	

    ESP_LOGI(TAG, ""TRAZAR" Leyendo desde el sensor", INFOTRAZA);
    while (error != ESP_OK) {

		error = read_temperature(&temperature);
		if (error == ESP_OK) {
			ESP_LOGI(TAG, ""TRAZAR" Lectura local correcta!. ", INFOTRAZA);
			temperatura_a_redondear = temperature + esp_rmaker_param_get_val(datosApp->calibrate)->val.f;
			temperature = redondear_temperatura(temperatura_a_redondear);

		} else {

			ESP_LOGE(TAG, ""TRAZAR" Error al leer desde el sensor de temperatura", INFOTRAZA);
		}

	
	}

	return error;
}

esp_err_t reading_remote_temperature(app_params *datosApp) {


	return ESP_OK;
}


void task_iotThermostat(void *args) 
{

	app_params *datosApp = (app_params*) args;
	esp_err_t error = ESP_OK ;




	/**
	 * init driver ds18b20
	 */
	init_ds18b20();
    ESP_LOGI(TAG, ""TRAZAR"COMIENZA LA TAREA DE LECTURA DE TEMPERATURA", INFOTRAZA);

    //lv_update_relay(gpio_get_level(RELAY_GPIO));

    while(1) {

		if (strcmp(esp_rmaker_param_get_val(datosApp->sensor)->val.s, NULSENSOR) == 0) {

			error = reading_remote_temperature(datosApp);

		} else {
			ESP_LOGW(TAG, ""TRAZAR" Leemos temperatura en local", INFOTRAZA);
			error = reading_local_temperature(datosApp);

		}

		if (error == ESP_OK) {
			vTaskDelay(esp_rmaker_param_get_val(datosApp->read_interval)->val.f * 1000 / portTICK_PERIOD_MS);
		} else {
			vTaskDelay(esp_rmaker_param_get_val(datosApp->read_interval)->val.f * 500 / portTICK_PERIOD_MS);
		}


	}
}


