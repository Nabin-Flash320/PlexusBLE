
#include <stdint.h>

#include "esp_log.h"

#include "NimBLEPortDefs.h"

#define TAG "ExampleService"

#define ExampleServiceWriteCharDesc1Value "Writable Characteristics"
#define ExampleServiceReadCharDesc1Value "Readable Characteristics"

static uint8_t writable_value[32] = {0};
static size_t writable_value_len = 0;

int ExampleServiceWriteCharAccessCallback(uint16_t conn_handle, uint16_t attr_handle,
                                          s_plexus_ble_access_context_t *ctxt, void *arg)
{
    ESP_LOGE(TAG, "ExampleServiceWriteCharAccessCallback: conn_handle=%d attr_handle=%d", conn_handle, attr_handle);
    ESP_LOGE(TAG, "Operation %d", ctxt->op);
    
    os_mbuf_copydata(ctxt->om, 0, sizeof(writable_value), writable_value);
    writable_value_len = ctxt->om->om_len;

    ESP_LOG_BUFFER_HEX(TAG, writable_value, sizeof(writable_value));
    return 0;
}

int ExampleServiceReadCharAccessCallback(uint16_t conn_handle, uint16_t attr_handle,
                                         s_plexus_ble_access_context_t *ctxt, void *arg)
{
    ESP_LOGE(TAG, "ExampleServiceReadCharAccessCallback: conn_handle=%d attr_handle=%d", conn_handle, attr_handle);
    ESP_LOGE(TAG, "Operation %d", ctxt->op);
    
    os_mbuf_append(ctxt->om, writable_value, writable_value_len);
    return 0;
}

int ExampleServiceWriteCharDesc1AccessCallback(uint16_t conn_handle, uint16_t attr_handle,
                                               s_plexus_ble_access_context_t *ctxt, void *arg)
{
    ESP_LOGE(TAG, "ExampleServiceWriteCharDesc1AccessCallback: conn_handle=%d attr_handle=%d", conn_handle, attr_handle);
    ESP_LOGE(TAG, "Operation %d", ctxt->op);
    
    os_mbuf_append(ctxt->om, ExampleServiceWriteCharDesc1Value, strlen(ExampleServiceWriteCharDesc1Value));
    return 0;
}

int ExampleServiceReadCharDesc1AccessCallback(uint16_t conn_handle, uint16_t attr_handle,
                                              s_plexus_ble_access_context_t *ctxt, void *arg)
{
    ESP_LOGE(TAG, "ExampleServiceReadCharDesc1AccessCallback: conn_handle=%d attr_handle=%d", conn_handle, attr_handle);
    ESP_LOGE(TAG, "Operation %d", ctxt->op);
    
    os_mbuf_append(ctxt->om, ExampleServiceReadCharDesc1Value, strlen(ExampleServiceReadCharDesc1Value));
    return 0;
}
