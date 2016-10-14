#c-utility
if(EXISTS "${CMAKE_INSTALL_PREFIX}/../azure_c_shared_utility/")
    set(SHARED_UTIL_INC_FOLDER "${CMAKE_INSTALL_PREFIX}/../azure_c_shared_utility/include/azureiot/" CACHE INTERNAL "this is what needs to be included if using sharedLib lib" FORCE)
    set(SHARED_UTIL_LIB "${CMAKE_INSTALL_PREFIX}../azure_c_shared_utility/lib/aziotsharedutil.lib" CACHE INTERNAL "this is what needs to be included if using sharedLib lib" FORCE)
else()
    #Will change to ExternalProject_Add
    add_subdirectory(./deps/c-utility)
endif()

#iot-sdk

#nanomsg

