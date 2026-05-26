
set(
    PLEXUS_BLE_SRC_DIRS 
    "PlexusBLE.c"
)


set(
    PLEXUS_BLE_INCLUDE_DIRS 
    .
    "NimBLEPort"
)

idf_component_register(SRCS ${PLEXUS_BLE_SRC_DIRS}
                       INCLUDE_DIRS "${PLEXUS_BLE_INCLUDE_DIRS}"
                       REQUIRES bt)

