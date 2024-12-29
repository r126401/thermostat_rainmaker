
#include "thermostat_task.h"
#include "app_main.h"


#include "esp_err.h"
#include "esp_log.h"
#include "alarms_app.h"
#include <string.h>
#include <math.h>
#include "time.h"
#include "onewire_bus.h"
#include "onewire_types.h"
#include "ds18b20.h"
#include <freertos/FreeRTOS.h>
#include "driver/gpio.h"
#include "lv_main_thermostat.h"
#include "events_app.h"
#include "schedule_app.h"
#include "events_lcd.h"


static const char *TAG = "thermostat_task";

#define ONEWIRE_MAX_DS18B20 1
ds18b20_device_handle_t ds18b20s[ONEWIRE_MAX_DS18B20];

extern esp_rmaker_device_t *thermostat_device;


static void init_ds18b20()
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

static esp_err_t read_temperature(float *temperature_metered) 

{
	esp_err_t error; 

	if (ds18b20_trigger_temperature_conversion(*ds18b20s) != ESP_OK) {
		ESP_LOGE(TAG, ""TRAZAR" Error al hacer la conversion de temperatura", INFOTRAZA);
		return ESP_FAIL;
	}
	if ((error = ds18b20_get_temperature(*ds18b20s, temperature_metered)) == ESP_OK) {

		//ESP_LOGI(TAG, "temperature read from DS18B20: %.2f C", temperature_metered);	
		//ESP_LOGI(TAG, "%s: TEMPERATURA ORIGINAL: %.02f C", esp_log_system_timestamp(), *temperature_metered);
		set_alarm(SENSOR_ALARM, ALARM_APP_OFF);

	} else {

		set_alarm(SENSOR_ALARM, ALARM_APP_ON);
	}

	

    return error;
    

}









#define DEFAULT_THRESHOLD 21.0



static enum THERMOSTAT_ACTION calcular_accion_termostato(STATUS_RELAY *accion, float current_temperature) {

	float margin_temperature;
	float threshold_temperature;
	esp_rmaker_param_t *param;
	//event_lcd_t event;
	//event.event_type = UPDATE_THRESHOLD_TEMPERATURE;


	param = esp_rmaker_device_get_param_by_name(thermostat_device, MARGIN_TEMPERATURE);
	if (param != NULL) {
		margin_temperature = esp_rmaker_param_get_val(param)->val.f;
	} else {
		margin_temperature = 0.5;
		ESP_LOGW(TAG, "rmaker no activo. Se introduce el valor por defecto para el margen de temperatura");
	}
	

	param = esp_rmaker_device_get_param_by_name(thermostat_device, SETPOINT_TEMPERATURE);
	if (param!= NULL) {
		
		threshold_temperature = esp_rmaker_param_get_val(param)->val.f;
		ESP_LOGE(TAG, "EL VALOR DE THRESHOLD ES : %.1f", threshold_temperature);
	} else {
		ESP_LOGW(TAG, "rmaker no activo. Se introduce el valor por defecto para el threshold");
		threshold_temperature = DEFAULT_THRESHOLD;

	}

	//event.value = threshold_temperature;
	//send_event_lcd(event);
	set_lcd_update_threshold_temperature(threshold_temperature);
	ESP_LOGI(TAG, "THRESHOLD : %.1f", threshold_temperature);
	

    if (gpio_get_level(CONFIG_RELAY_GPIO) == OFF) {
               if (current_temperature <= (threshold_temperature - margin_temperature)) {
            	   ESP_LOGI(TAG, ""TRAZAR"RELE OFF Y SE ENCIENDE. tempMedida: %.2f, tempUmbral: %.02f", INFOTRAZA, current_temperature, threshold_temperature);
                   *accion = ON;
                   return TOGGLE_THERMOSTAT;
               } else {
            	   ESP_LOGI(TAG, ""TRAZAR"RELE OFF Y DEBE SEGUIR SIGUE OFF. tempMedida: %.2f, tempUmbral: %.02f", INFOTRAZA, current_temperature, threshold_temperature);
                   *accion = OFF;
                   return NO_TOGGLE_THERMOSTAT;

               }
           } else {
               if (current_temperature >= (threshold_temperature + margin_temperature) ) {
            	   ESP_LOGI(TAG, ""TRAZAR"RELE ON Y SE APAGA. tempMedida: %.2f, tempUmbral: %.02f", INFOTRAZA, current_temperature, threshold_temperature);
                   *accion = OFF;
                   return TOGGLE_THERMOSTAT;
               } else {
            	   ESP_LOGI(TAG, ""TRAZAR"RELE ON Y DEBE SEGUIR SIGUE ON. tempMedida: %.2f, tempUmbral: %.02f", INFOTRAZA, current_temperature, threshold_temperature);
                   *accion = ON;
                   return NO_TOGGLE_THERMOSTAT;

               }
           }

		

}


THERMOSTAT_ACTION thermostat_action(float current_temperature) {

	enum STATUS_RELAY accion_rele;
	enum THERMOSTAT_ACTION accion_termostato;
	esp_rmaker_param_t *param;
	float temperature;

	ESP_LOGI(TAG, "Estamos en thermostat_action");

	param = esp_rmaker_device_get_param_by_name(thermostat_device, MODE);
	//ESP_LOGI(TAG, "Estamos en thermostat_action en modo %s", esp_rmaker_param_get_val(param)->val.s);
	if (param != NULL) {

		if (strcmp(esp_rmaker_param_get_val(param)->val.s, TEXT_STATUS_APP_MANUAL) == 0) {

			ESP_LOGW(TAG, "No se hace nada ya que tenemos el termostato en modo manual");
			return NO_ACTION_THERMOSTAT;

		}

		param = esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_TEMPERATURE_NAME);
		temperature = esp_rmaker_param_get_val(param)->val.f;


	} else {
		temperature = current_temperature;
	}


//	if (current_temperature != temperature) {

	ESP_LOGI(TAG, ""TRAZAR"accionar_termostato: LECTURA ANTERIOR: %.2f, LECTURA POSTERIOR: %.2f HA HABIDO CAMBIO DE TEMPERATURA", INFOTRAZA,
			temperature, current_temperature);

    if (((accion_termostato = calcular_accion_termostato(&accion_rele, current_temperature)) == TOGGLE_THERMOSTAT)) {
    	ESP_LOGI(TAG, ""TRAZAR"VAMOS A ACCIONAR EL RELE", INFOTRAZA);
    	//*******hacer relay_operation(datosApp, TEMPORIZADA, accion_rele);
		relay_operation(accion_rele);
    } else {
		accion_termostato = NO_TOGGLE_THERMOSTAT;
		//ESP_LOGW(TAG, "Temperatura anterior: %.2f, Temperatura actual: %.2f. No se hace nada porque son iguales.", temperature, current_temperature);
		}
	//} else {
	//	accion_termostato = NINGUNA_ACCION;
	//			ESP_LOGW(TAG, "Temperatura anterior: %.2f, Temperatura actual: %.2f. No se hace nada porque son iguales.", temperature, current_temperature);

	//}



    
	return accion_termostato;
}



static float redondear_temperatura(float temperatura) {

	float redondeado;
	float diferencia;
	float resultado = 0;
	float valor_absoluto;

	redondeado = lround(temperatura);
	diferencia = temperatura - redondeado;
	//ESP_LOGE(TAG, "temperatura: %.2f, redondeado: %.2f, diferencia: %.2f", temperatura, redondeado, diferencia);
	if (diferencia == 0) {
		resultado = temperatura;
		//ESP_LOGI(TAG, ""TRAZAR"TEMPERATURA ORIGINAL: %.2f, TEMPERATURA REDONDEADA: %.2f,", INFOTRAZA, temperatura, resultado);
		return resultado;

	}
	valor_absoluto = fabs(redondeado);
	//ESP_LOGE(TAG, "temperatura: %.2f, redondeado: %.2f, diferencia: %.2f, valor absoluto :%.2f", temperatura, redondeado, diferencia, valor_absoluto);
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



esp_err_t reading_local_temperature(float *current_temperature) {

    esp_err_t error = ESP_FAIL;
	float temperatura_a_redondear;
	//float current_temperature;
	float calibrate;
	esp_rmaker_param_t *param;


	param = esp_rmaker_device_get_param_by_name(thermostat_device, CALIBRATE);
	if (param != NULL) {
		calibrate = esp_rmaker_param_get_val(param)->val.f;

	} else {
		calibrate = -3.5;
		ESP_LOGW(TAG, "rmaker no activo. Se introduce el valor por defecto de calibrate");
	}
	



    ESP_LOGI(TAG, ""TRAZAR" Leyendo desde el sensor. Calibrado: %.2f", INFOTRAZA, calibrate);


	error = read_temperature(current_temperature);
	if (error == ESP_OK) {
		ESP_LOGI(TAG, ""TRAZAR" Lectura local correcta!. ", INFOTRAZA);
		temperatura_a_redondear = *current_temperature + calibrate;
		*current_temperature = redondear_temperatura(temperatura_a_redondear);
		thermostat_action(*current_temperature);
		ESP_LOGI(TAG, "Actualizada y enviada la temperatura actualizada: %.2f", *current_temperature);
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
	float current_temperature;
	//event_lcd_t event;
	//event.event_type = UPDATE_TEMPERATURE;


	/**
	 * init driver ds18b20
	 */

	relay_operation(false);

	
	init_ds18b20();
    ESP_LOGI(TAG, "COMIENZA LA TAREA DE LECTURA DE TEMPERATURA");

    while(1) {

		//reading_temperature();


		param = esp_rmaker_device_get_param_by_name(thermostat_device, READ_INTERVAL);
		if (param != NULL) {
			value = esp_rmaker_param_get_val(param)->val.i;

		} else {
			ESP_LOGW(TAG, "Rmaker no activo, read_interval se pone por defecto a 60sg");
			value = 60;
		}
		param = esp_rmaker_device_get_param_by_name(thermostat_device, ID_SENSOR);
		if (param != NULL) {
			id_sensor = esp_rmaker_param_get_val(param)->val.s;
		} else {
			id_sensor = NULSENSOR;
			ESP_LOGW(TAG, "Rmaker no activo, id sensor se pone a Null para la lectura en local");
		}
		

		ESP_LOGI(TAG, "Intervalo lectura: %d, id_sensor: %s", value, id_sensor);



		if (strcmp(id_sensor, NULSENSOR) == 0) {

			ESP_LOGW(TAG, ""TRAZAR" Leemos temperatura en local", INFOTRAZA);
			error = reading_local_temperature(&current_temperature);
			if (error == ESP_OK) {
				//event.value = current_temperature;
				//send_event_lcd(event);
				set_lcd_update_temperature(current_temperature);
				ESP_LOGI(TAG, "Enviada la temperatura al display");
				param = esp_rmaker_device_get_param_by_name(thermostat_device, ESP_RMAKER_DEF_TEMPERATURE_NAME);
				if (param != NULL) {
					esp_rmaker_param_update_and_report(param, esp_rmaker_float(current_temperature));
				} else {
					ESP_LOGW(TAG, "Rmaker no activo, No se reporta el valor de la temperatura");
				}
				

			}

			

		} else {
			ESP_LOGW(TAG, ""TRAZAR" Leemos temperatura en remoto", INFOTRAZA);
			error = reading_remote_temperature();

		}

		ESP_LOGE(TAG, "LOS HEMOS LEIDO");
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


