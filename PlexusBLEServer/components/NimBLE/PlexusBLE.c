
#include <string.h>
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_mac.h"

#include "host/ble_uuid.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "host/ble_gatt.h"
#include "host/ble_gap.h"
#include "host/ble_hs.h"

#include "NimBLEPort.h"
#include "PlexusBLE.h"
#include "NimBLEPortDefs.h"
#include "PlexusServiceDefs.h"

#define TAG "PlexusBLE"

#define DECLARE_EXAMPLE_SERVICE 1
#include "ExampleServiceDeclare.h"
#undef DECLARE_EXAMPLE_SERVICE

void PlexusBLEInit(void)
{
	esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
	ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));

	NimBLEPortInit();
	NimBLEAddService(plexus_example_service);
	NimBLEPortStart();
}
