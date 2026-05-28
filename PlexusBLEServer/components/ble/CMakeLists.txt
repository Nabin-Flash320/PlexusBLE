
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
        "NimBLE/NimBLEPort/NimBLEPort.c"
        "NimBLE/NimBLEPort/NimBLEPortGap.c"
        "NimBLE/Services/ExampleService/ExampleService.c"
    )
    
    list(
        APPEND PLEXUS_BLE_INCLUDE_DIRS 
        "NimBLE/NimBLEPort"
        "NimBLE/Services/ExampleService"
    )

elseif(CONFIG_BT_BLUEDROID_ENABLED)   

    list (
        APPEND PLEXUS_BLE_SRC_DIRS
        "Bluedroid/ble.c"
        "Bluedroid/ble_gap.c"
        "Bluedroid/ble_gatts.c"
        "Bluedroid/Services/example_service_handler.c"
    )

     list(
        APPEND PLEXUS_BLE_INCLUDE_DIRS 
        "Bluedroid"
        "Bluedroid/Services"
    )

endif()

idf_component_register(SRCS ${PLEXUS_BLE_SRC_DIRS}
                       INCLUDE_DIRS "${PLEXUS_BLE_INCLUDE_DIRS}"
                       REQUIRES bt)

