
#ifndef __NIMBLE_PORT_DEFS_H__
#define __NIMBLE_PORT_DEFS_H__


#include "host/ble_gatt.h"
#include "host/ble_gap.h"
#include "host/ble_hs.h"


#define PLEXUS_END_MARKER               BLE_GATT_SVC_TYPE_END

#define PLEXUS_SERVICE_END              PLEXUS_END_MARKER
#define PLEXUS_CHR_END                  PLEXUS_END_MARKER
#define PLEXUS_DSC_END                  PLEXUS_END_MARKER

// typedefs for NimBLE gatt to be used in PlexusBLE to avoid including NimBLE headers 
typedef struct ble_gatt_svc_def         s_plexus_ble_service_t;
typedef struct ble_gatt_chr_def         s_plexus_ble_characteristic_t;
typedef struct ble_gatt_dsc_def         s_plexus_ble_descriptor_t;

typedef struct ble_gatt_access_ctxt     s_plexus_ble_access_context_t;

// typedefs for NimBLE gap to be used in PlexusBLE to avoid including NimBLE headers 
typedef struct ble_gap_event            s_plexus_ble_gap_event_t;

// typedefs for NimBLE hs to be used in PlexusBLE to avoid including NimBLE headers 
typedef struct ble_hs_cfg               s_plexus_ble_hs_cfg_t;

#endif /* __NIMBLE_PORT_DEFS_H__ */

