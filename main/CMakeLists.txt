idf_component_register(SRCS 
./app_driver.c 
./app_main.c 
./thermostat_task.c 
./rgblcd.c
./events_app.c
./schedule_app.c
./alarms_app.c
lcd/lv_factory_thermostat.c 
lcd/lv_main_thermostat.c 
lcd/lv_styles_thermostat.c
lcd/events_lcd.c
lcd/fonts/russo36.c 
lcd/fonts/russo48.c
lcd/images/ic_heating.c 
lcd/images/ic_thermometer.c 
lcd/images/ic_threshold.c 
lcd/images/ic_warning.c 




                       INCLUDE_DIRS "."

INCLUDE_DIRS "." "include" lcd/include)
