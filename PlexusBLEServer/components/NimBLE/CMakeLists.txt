
set(
    PLEXUS_BLE_SRC_DIRS 
    "PlexusBLE.c"
    "NimBLEPort/NimBLEPort.c"
    "NimBLEPort/NimBLEPortGap.c"
    "PlexusServices/ExampleService/ExampleService.c"
)

set(
    PLEXUS_BLE_INCLUDE_DIRS 
    .
    "NimBLEPort"
    "PlexusServices/ExampleService"
)

idf_component_register(SRCS ${PLEXUS_BLE_SRC_DIRS}
                       INCLUDE_DIRS "${PLEXUS_BLE_INCLUDE_DIRS}"
                       REQUIRES bt)

