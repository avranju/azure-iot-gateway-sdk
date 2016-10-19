if(NOT azure_c_shared_utility_FOUND)
    find_package(azure_c_shared_utility REQUIRED CONFIG)
endif()

add_library(nanomsg STATIC IMPORTED)
set_target_properties(nanomsg PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/../../nanomsg/include/nanomsg"
    IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/../../nanomsg/lib/nanomsg.lib"
)

if(WIN32)
    file(
        INSTALL
            "${CMAKE_CURRENT_LIST_DIR}/../../nanomsg/bin/nanomsg.dll"
        DESTINATION
            "${CMAKE_CURRENT_BINARY_DIR}"
    )
endif()

set(nanomsg_FOUND 1 CACHE INTERNAL "")

include("${CMAKE_CURRENT_LIST_DIR}/azure_iot_gateway_sdkTargets.cmake")