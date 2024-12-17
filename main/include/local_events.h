

#include "esp_err.h"
#include "esp_rmaker_core.h"
#include <esp_rmaker_standard_types.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_standard_devices.h>
#include <esp_rmaker_schedule.h>
#include <esp_rmaker_scenes.h>
#include <esp_rmaker_console.h>
#include <esp_rmaker_ota.h>
#include <esp_rmaker_utils.h>

#include "esp_rmaker_schedule.h"


/*
typedef enum {
    ESP_RMAKER_STATE_DEINIT = 0,
    ESP_RMAKER_STATE_INIT_DONE,
    ESP_RMAKER_STATE_STARTING,
    ESP_RMAKER_STATE_STARTED,
    ESP_RMAKER_STATE_STOP_REQUESTED,
} esp_rmaker_state_t;

typedef struct {
    esp_rmaker_param_val_t min;
    esp_rmaker_param_val_t max;
    esp_rmaker_param_val_t step;
} esp_rmaker_param_bounds_t;

typedef struct {
    uint8_t str_list_cnt;
    const char **str_list;
} esp_rmaker_param_valid_str_list_t;

typedef struct esp_rmaker_param {
    char *name;
    char *type;
    uint8_t flags;
    uint8_t prop_flags;
    char *ui_type;
    esp_rmaker_param_val_t val;
    esp_rmaker_param_bounds_t *bounds;
    esp_rmaker_param_valid_str_list_t *valid_str_list;
    struct esp_rmaker_device *parent;
    struct esp_rmaker_param * next;
}esp_rmaker_param;


typedef struct esp_rmaker_attr {
    char *name;
    char *value;
    struct esp_rmaker_attr *next;
}esp_rmaker_attr;
typedef struct esp_rmaker_attr esp_rmaker_attr_t;


typedef struct esp_rmaker_device {
    char *name;
    char *type;
    char *subtype;
    char *model;
    uint8_t param_count;
    esp_rmaker_device_write_cb_t write_cb;
    esp_rmaker_device_read_cb_t read_cb;
    esp_rmaker_device_bulk_write_cb_t bulk_write_cb;
    esp_rmaker_device_bulk_read_cb_t bulk_read_cb;
    void *priv_data;
    bool is_service;
    esp_rmaker_attr_t *attributes;
    esp_rmaker_param_t *params;
    esp_rmaker_param_t *primary;
    const esp_rmaker_node_t *parent;
    struct esp_rmaker_device *next;
}esp_rmaker_device;
typedef struct esp_rmaker_device _esp_rmaker_device_t;

typedef struct {
    char *node_id;
    esp_rmaker_node_info_t *info;
    esp_rmaker_attr_t *attributes;
    _esp_rmaker_device_t *devices;
} _esp_rmaker_node_t;


*/





esp_err_t write_cb(const esp_rmaker_device_t *device, const esp_rmaker_param_t *param,
            const esp_rmaker_param_val_t val, void *priv_data, esp_rmaker_write_ctx_t *ctx);
void update_threshold(float threshold, bool reporting);