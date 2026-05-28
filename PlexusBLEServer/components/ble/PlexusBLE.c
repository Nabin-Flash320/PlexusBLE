

#include <sdkconfig.h>
#include "esp_bt.h"

#ifdef CONFIG_BT_NIMBLE_ENABLED

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

#elif defined(CONFIG_BT_BLUEDROID_ENABLED)

#include "ble.h"

#endif //  CONFIG_BT_NIMBLE_ENABLED

#define TAG "PlexusBLE"

#ifdef CONFIG_BT_NIMBLE_ENABLED
#define DECLARE_EXAMPLE_SERVICE 1
#include "ExampleServiceDeclare.h"
#undef DECLARE_EXAMPLE_SERVICE
#endif // CONFIG_BT_NIMBLE_ENABLED

void PlexusBLEInit(void)
{
	esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
	ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));

#ifdef CONFIG_BT_NIMBLE_ENABLED
	NimBLEPortInit();
	NimBLEAddService(plexus_example_service);
	NimBLEPortStart();
#elif defined(CONFIG_BT_BLUEDROID_ENABLED)
	ble_init();
#endif // CONFIG_BT_NIMBLE_ENABLED
}
