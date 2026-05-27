
#include "esp_mac.h"
#include "host/ble_uuid.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "host/ble_gatt.h"
#include "host/ble_gap.h"
#include "host/ble_hs.h"

#include "NimblePort.h"

#define TAG "NimBLE-Port"

static void nimbleHostTask(void *params);
static void nimbleOnSync(void);
static void nimbleOnReset(int reason);
static void plexusStartAdvertising(void);

void NimBLEPortInit()
{
    esp_nimble_init();

    ble_hs_cfg.sync_cb = nimbleOnSync;
    ble_hs_cfg.reset_cb = nimbleOnReset;

    ble_svc_gap_init();
    ble_svc_gatt_init();
}

void NimBLEPortStart()
{
    esp_nimble_enable(nimbleHostTask);
}

int NimBLEAddService(const s_plexus_ble_service_t *service)
{
    if(!service)
    {
        ESP_LOGE(TAG, "No service provided");
        return -1;
    }

    ble_gatts_count_cfg(service);
    ble_gatts_add_svcs(service);

    return 0;
}

static void nimbleHostTask(void *params)
{
    nimble_port_run();
    esp_nimble_disable();
}

static void nimbleOnSync(void)
{
    // Pick a random private address
    ble_addr_t addr;
    ble_hs_id_gen_rnd(1, &addr);
    ble_hs_id_set_rnd(addr.val);

    plexusStartAdvertising();
}

static void nimbleOnReset(int reason)
{
    ESP_LOGE(TAG, "BLE host reset, reason: %d", reason);
}

static void plexusStartAdvertising(void)
{
	struct ble_gap_adv_params adv_params = {0};
	struct ble_hs_adv_fields fields = {0};

	// Advertised name
	char name[32] = {0};
	uint8_t mac[6] = {0};
	esp_read_mac(mac, ESP_MAC_BT);
	snprintf(name, sizeof(name), "PlexusDev-%02x:%02x", mac[4], mac[5]);
	fields.name = (uint8_t *)name;
	fields.name_len = strlen(name);
	fields.name_is_complete = 1;

	// Flags: general discoverable, BR/EDR not supported
	fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;

	ble_gap_adv_set_fields(&fields);

	// Undirected connectable advertising
	adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
	adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;

	int rc = ble_gap_adv_start(BLE_OWN_ADDR_RANDOM, NULL, BLE_HS_FOREVER,
							   &adv_params, PlexusGapEventHandler, NULL);
	if (rc != 0)
	{
		ESP_LOGE(TAG, "Advertising start failed: %d", rc);
	}
	else
	{
		ESP_LOGI(TAG, "Advertising started");
	}
}

