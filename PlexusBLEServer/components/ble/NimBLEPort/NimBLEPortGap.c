
#include "NimBLEPortDefs.h"

#define TAG "NimBLE-Gap"

int PlexusGapEventHandler(s_plexus_ble_gap_event_t *event, void *arg)
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


