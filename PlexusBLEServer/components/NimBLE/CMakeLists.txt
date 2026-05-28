
set (
    PLEXUS_BLE_SRC_DIRS
    "PlexusBLE.c"
)

set(
    PLEXUS_BLE_INCLUDE_DIRS 
    .
)


if(CONFIG_BT_NIMBLE_ENABLED)

    list(
        APPEND PLEXUS_BLE_SRC_DIRS 
        "NimBLEPort/NimBLEPort.c"
        "NimBLEPort/NimBLEPortGap.c"
        "PlexusServices/ExampleService/ExampleService.c"
    )
    
    list(
        APPEND PLEXUS_BLE_INCLUDE_DIRS 
        "NimBLEPort"
        "PlexusServices/ExampleService"
        )
        
endif()

idf_component_register(SRCS ${PLEXUS_BLE_SRC_DIRS}
                       INCLUDE_DIRS "${PLEXUS_BLE_INCLUDE_DIRS}"
                       REQUIRES bt)

