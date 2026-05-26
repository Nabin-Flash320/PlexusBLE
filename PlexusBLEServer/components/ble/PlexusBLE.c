
#include <string.h>
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_mac.h"

#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "host/ble_gatt.h"
#include "host/ble_gap.h"
#include "host/ble_hs.h"

#include "PlexusBLE.h"
#include "NimBLEPortDefs.h"

#define TAG "PlexusBLE"

static int plexusGattServiceCharacteristicsAccess(uint16_t conn_handle, uint16_t attr_handle,
												  struct ble_gatt_access_ctxt *ctxt, void *arg);
static int plexusGapEventHandler(s_plexus_ble_gap_event_t *event, void *arg);
static void plexusStartAdvertising(void);

static const s_plexus_ble_characteristic_t gatt_svr_chr[] = {
	{
		.uuid = BLE_UUID16_DECLARE(0x2A19),
		.access_cb = plexusGattServiceCharacteristicsAccess,
		.flags = BLE_GATT_CHR_F_READ,
	},
	{
		PLEXUS_CHR_END,
	},
};

static const s_plexus_ble_service_t gatt_svr_svcs[] = {
	{
		.type = BLE_GATT_SVC_TYPE_PRIMARY,
		.uuid = BLE_UUID16_DECLARE(0x180F),
		.characteristics = gatt_svr_chr,
	},
	{
		PLEXUS_SERVICE_END,
	},
};

static void plexusOnSync(void)
{
	// Pick a random private address
	ble_addr_t addr;
	ble_hs_id_gen_rnd(1, &addr);
	ble_hs_id_set_rnd(addr.val);

	plexusStartAdvertising();
}

static void plexusOnReset(int reason)
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
							   &adv_params, plexusGapEventHandler, NULL);
	if (rc != 0)
	{
		ESP_LOGE(TAG, "Advertising start failed: %d", rc);
	}
	else
	{
		ESP_LOGI(TAG, "Advertising started");
	}
}

static void plexusHostTask(void *param)
{
	nimble_port_run();          // blocks — runs the NimBLE event loop
	esp_nimble_disable();       // only reached on shutdown
}

void PlexusBLEInit(void)
{
	esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
	ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));

	esp_nimble_init();

	ble_hs_cfg.sync_cb  = plexusOnSync;
	ble_hs_cfg.reset_cb = plexusOnReset;

	ble_svc_gap_init();
	ble_svc_gatt_init();

	ble_gatts_count_cfg(gatt_svr_svcs);
	ble_gatts_add_svcs(gatt_svr_svcs);

	esp_nimble_enable(plexusHostTask);  // spawns the host task — sync_cb fires from here
}

static int plexusGapEventHandler(s_plexus_ble_gap_event_t *event, void *arg)
{

	ESP_LOGE(TAG, "Event type: %d", event->type);
	switch (event->type)
	{
	case BLE_GAP_EVENT_CONNECT:
	{
		ESP_LOGE(TAG, "Connect event status: %d", event->connect.status);
		ESP_LOGE(TAG, "Incoming connection at %d", event->connect.conn_handle);
		break;
	}
	case BLE_GAP_EVENT_MTU:
	{
		ESP_LOGE(TAG, "Handle: %d upgraded mtu to %d", event->mtu.conn_handle, event->mtu.value);
		break;
	}
	case BLE_GAP_EVENT_DATA_LEN_CHG:
	{
		ESP_LOGE(TAG, "Handle: %d(tx: %d; rx: %d)", event->data_len_chg.conn_handle, event->data_len_chg.max_tx_octets, event->data_len_chg.max_rx_octets);
		break;
	}
	default:
	{
		break;
	}
	}
	return 0;
}

static int plexusGattServiceCharacteristicsAccess(uint16_t conn_handle, uint16_t attr_handle,
												  struct ble_gatt_access_ctxt *ctxt, void *arg)
{
	ESP_LOGE(TAG, "plexusGattServiceCharacteristicsAccess: conn_handle=%d attr_handle=%d", conn_handle, attr_handle);
	return 0;
}
