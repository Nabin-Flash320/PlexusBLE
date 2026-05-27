

#ifndef __NIMBLE_PORT_H__
#define __NIMBLE_PORT_H__

#include "NimBLEPortDefs.h"

void NimBLEPortInit();
void NimBLEPortStart();
int NimBLEAddService(const s_plexus_ble_service_t *service);

int PlexusGapEventHandler(s_plexus_ble_gap_event_t *event, void *arg);

#endif // __NIMBLE_PORT_H__

