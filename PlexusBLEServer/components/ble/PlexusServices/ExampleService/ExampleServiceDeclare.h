
#ifndef __EXAMPLE_SERVICE_DECLARATION_H__
#define __EXAMPLE_SERVICE_DECLARATION_H__

#if DECLARE_EXAMPLE_SERVICE
#include "NimBLEPortDefs.h"
#include "PlexusServiceDefs.h"

extern int ExampleServiceWriteCharAccessCallback(uint16_t conn_handle, uint16_t attr_handle,
                                                 s_plexus_ble_access_context_t *ctxt, void *arg);
extern int ExampleServiceReadCharAccessCallback(uint16_t conn_handle, uint16_t attr_handle,
                                                s_plexus_ble_access_context_t *ctxt, void *arg);
extern int ExampleServiceWriteCharDesc1AccessCallback(uint16_t conn_handle, uint16_t attr_handle,
                                                      s_plexus_ble_access_context_t *ctxt, void *arg);
extern int ExampleServiceReadCharDesc1AccessCallback(uint16_t conn_handle, uint16_t attr_handle,
                                                     s_plexus_ble_access_context_t *ctxt, void *arg);
static s_plexus_ble_descriptor_t write_char_desc[] = {
    {
        .uuid = BLE_UUID128_DECLARE(PLEXUS_CUSTOM_SERVICE_WRITE_CHAR_DESCRIPTOR_1_UUID),
        .access_cb = ExampleServiceWriteCharDesc1AccessCallback,
        .att_flags = BLE_ATT_F_READ,
    },
    {
        PLEXUS_DSC_END,
    },
};

static s_plexus_ble_descriptor_t read_char_desc[] = {
    {
        .uuid = BLE_UUID128_DECLARE(PLEXUS_CUSTOM_SERVICE_READ_CHAR_DESCRIPTOR_1_UUID),
        .access_cb = ExampleServiceReadCharDesc1AccessCallback,
        .att_flags = BLE_ATT_F_READ,
    },
    {
        PLEXUS_DSC_END,
    },
};

static const s_plexus_ble_characteristic_t gatt_svr_chr[] = {
    {
        .uuid = BLE_UUID128_DECLARE(PLEXUS_CUSTOM_SERVICE_WRITE_CHAR_UUID),
        .access_cb = ExampleServiceWriteCharAccessCallback,
        .flags = BLE_GATT_CHR_F_WRITE,
        .descriptors = write_char_desc,
    },
    {
        .uuid = BLE_UUID128_DECLARE(PLEXUS_CUSTOM_SERVICE_READ_CHAR_UUID),
        .access_cb = ExampleServiceReadCharAccessCallback,
        .flags = BLE_GATT_CHR_F_READ,
        .descriptors = read_char_desc,
    },
    {
        PLEXUS_CHR_END,
    },
};

static const s_plexus_ble_service_t gatt_svr_svcs[] = {
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID128_DECLARE(PLEXUS_CUSTOM_SERVICE_UUID),
        .characteristics = gatt_svr_chr,
    },
    {
        PLEXUS_SERVICE_END,
    },
};
#endif // DECLARE_EXAMPLE_SERVICE

#endif // __EXAMPLE_SERVICE_DECLARATION_H__
