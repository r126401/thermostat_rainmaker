
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

		//ESP_LOGI(TAG, "temperature read from DS18B20: %.2f C", temperature_metered);	
		ESP_LOGI(TAG, "%s: TEMPERATURA ORIGINAL: %.02f C", esp_log_system_timestamp(), *temperature_metered);

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
/*
enum ESTADO_RELE relay_operation(DATOS_APLICACION *datosApp, enum TIPO_ACTUACION_RELE tipo, enum ESTADO_RELE operacion) {

	enum ESTADO_RELE rele;

	switch (tipo) {
	case MANUAL:
		if (gpio_get_level(CONFIG_GPIO_PIN_RELE) == OFF) {
			ESP_LOGW(TAG, ""TRAZAR" ESTABA A OFF Y SE ENCIENDE", INFOTRAZA);
			rele = ON;
		} else {
			ESP_LOGW(TAG, ""TRAZAR" ESTABA A On Y SE APAGA", INFOTRAZA);
			rele = OFF;
		}
		break;
	default:
		rele = operacion;
		break;
	}
	//gpio_rele_out();
	gpio_set_level(CONFIG_GPIO_PIN_RELE, rele);
	ESP_LOGW(TAG, ""TRAZAR"EL RELE SE HA PUESTO A %d", INFOTRAZA, rele);
	lv_update_relay(rele);
	if (get_current_status_application(datosApp) == FACTORY) {
	}

	return rele;
}


void thermostat_action(DATOS_APLICACION *datosApp) {

	enum ESTADO_RELE accion_rele;
	enum TIPO_ACCION_TERMOSTATO accion_termostato;
	static float lecturaAnterior = -1000;

	if (get_current_status_application(datosApp) == NORMAL_MANUAL) {
		ESP_LOGW(TAG, ""TRAZAR"SE RETORNA PORQUE LA APLICACION ESTA EN ESTADO NORMAL_MANUAL", INFOTRAZA);
		return;
	}

	ESP_LOGI(TAG, ""TRAZAR"accionar_termostato: LECTURA ANTERIOR: %.2f, LECTURA POSTERIOR: %.2f HA HABIDO CAMBIO DE TEMPERATURA", INFOTRAZA,
			lecturaAnterior, datosApp->termostato.tempActual);

    if (((accion_termostato = calcular_accion_termostato(datosApp, &accion_rele)) == ACCIONAR_TERMOSTATO)) {
    	ESP_LOGI(TAG, ""TRAZAR"VAMOS A ACCIONAR EL RELE", INFOTRAZA);
    	relay_operation(datosApp, TEMPORIZADA, accion_rele);
    }

    if ((accion_termostato == ACCIONAR_TERMOSTATO) || (lecturaAnterior != datosApp->termostato.tempActual)) {
    	ESP_LOGI(TAG, ""TRAZAR"HA HABIDO CAMBIO DE TEMPERATURA", INFOTRAZA);
        send_spontaneous_report(datosApp, CHANGE_TEMPERATURE);

    }
    lecturaAnterior = datosApp->termostato.tempActual;
}

*/

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



esp_err_t reading_local_temperature() {

    esp_err_t error = ESP_FAIL;
	float temperatura_a_redondear;
	float temperature;
	float calibrate;
	esp_rmaker_param_t *param;


	param = esp_rmaker_device_get_param_by_name(thermostat_device, CALIBRATE);
	calibrate = esp_rmaker_param_get_val(param)->val.f;

	param = esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_TEMPERATURE_NAME);


    ESP_LOGI(TAG, ""TRAZAR" Leyendo desde el sensor. Calibrado: %.2f", INFOTRAZA, calibrate);


	error = read_temperature(&temperature);
	if (error == ESP_OK) {
		ESP_LOGI(TAG, ""TRAZAR" Lectura local correcta!. ", INFOTRAZA);
		temperatura_a_redondear = temperature + calibrate;
		temperature = redondear_temperatura(temperatura_a_redondear);
		esp_rmaker_param_update_and_report(param, esp_rmaker_float(temperature));
		ESP_LOGI(TAG, "Actualizada y enviada la temperatura actualizada: %.2f", temperature);
	} else {
		ESP_LOGE(TAG, ""TRAZAR" Error al leer desde el sensor de temperatura", INFOTRAZA);
	}

	


	return error;
}

esp_err_t reading_remote_temperature() {


	return ESP_OK;
}


void task_iotThermostat() 
{

	esp_err_t error = ESP_OK ;
	int value;
	esp_rmaker_param_t *param;
	char* id_sensor;
	static uint8_t n_errors = 0;






	/**
	 * init driver ds18b20
	 */
	init_ds18b20();
    ESP_LOGI(TAG, "COMIENZA LA TAREA DE LECTURA DE TEMPERATURA");

    while(1) {

		param = esp_rmaker_device_get_param_by_name(thermostat_device, READ_INTERVAL);
		value = esp_rmaker_param_get_val(param)->val.i;
		param = esp_rmaker_device_get_param_by_name(thermostat_device, ID_SENSOR);
		id_sensor = esp_rmaker_param_get_val(param)->val.s;

		ESP_LOGI(TAG, "Intervalo lectura: %d, id_sensor: %s", value, id_sensor);



		if (strcmp(id_sensor, NULSENSOR) == 0) {

			ESP_LOGW(TAG, ""TRAZAR" Leemos temperatura en local", INFOTRAZA);
			error = reading_local_temperature();

			

		} else {
			ESP_LOGW(TAG, ""TRAZAR" Leemos temperatura en remoto", INFOTRAZA);
			error = reading_remote_temperature();

		}

		if (error == ESP_OK) {
			n_errors = 0;
			vTaskDelay(value * 1000 / portTICK_PERIOD_MS);
		} else {
			n_errors++;
			if (n_errors > CONFIG_ERROR_READING_TEMPERATURE) {

				ESP_LOGI(TAG, "Llevamos %d errores de lectura consecutivos", n_errors);
				esp_rmaker_param_update_and_notify(esp_rmaker_device_get_param_by_name(thermostat_device, ALARM), esp_rmaker_int(SENSOR_FAIL));

			}

			ESP_LOGE(TAG, "Error al leer la temperatura del dispositivo. Reintentamos en %d segundos", value);
			vTaskDelay(value * 500 / portTICK_PERIOD_MS);
		}


	}
	
}


