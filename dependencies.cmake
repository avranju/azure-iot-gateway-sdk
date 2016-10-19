#c-utility
find_package(azure_c_shared_utility CONFIG)
if(${azure_c_shared_utility_FOUND})
    set(SHARED_UTIL_INC_FOLDER ${AZURE_C_SHARED_UTILITY_INCLUDE_DIR} CACHE INTERNAL "this is what needs to be included if using sharedLib lib" FORCE)
    set(SHARED_UTIL_LIB_FOLDER ${AZURE_C_SHARED_LIBRARY_DIR} CACHE INTERNAL "this is what needs to be included if using sharedLib lib" FORCE)
    set(SHARED_UTIL_LIB aziotsharedutil CACHE INTERNAL "this is what needs to be included if using sharedLib lib" FORCE)
else()
    #Will change to ExternalProject_Add
    #add_subdirectory(./deps/c-utility)
    message(FATAL_ERROR "C utility lib not found")
    find_package(azure_c_shared_utility REQUIRED CONFIG)
endif()

#iot-sdk

#nanomsg
set(nanomsg_target_dll "${CMAKE_INSTALL_PREFIX}/../nanomsg/bin/nanomsg.dll" CACHE INTERNAL "The location of the nanomsg.dll (windows)" FORCE)
add_library(nanomsg STATIC IMPORTED)
set_target_properties(nanomsg PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/../nanomsg/include/nanomsg"
    IMPORTED_LOCATION "${CMAKE_INSTALL_PREFIX}/../nanomsg/lib/nanomsg.lib"
)

#include(FindPkgCOnfig)
#find_package(PkgConfig REQUIRED)
#pkg_search_module(NANOMSG REQUIRED nanomsg)
