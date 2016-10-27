# app sources
include_directories(../../modules/common)
include_directories(./inc)

set(native_sources
    ./src/native.c
)
set(native_headers
    ./inc/native.h
)

# build nodejs_binding module as a dynamic library
add_library(native_binding MODULE ${native_sources} ${native_headers})
target_link_libraries(native_binding gateway)
linkSharedUtil(native_binding)

add_binding_to_solution(native_binding)

if(install_modules)
    install(TARGETS native_binding LIBRARY DESTINATION "${LIB_INSTALL_DIR}/modules")
endif()
