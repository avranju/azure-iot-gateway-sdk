// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>

#ifdef _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "azure_c_shared_utility/gballoc.h"
#include "azure_c_shared_utility/xlogging.h"

#include "module_access.h"
#include "native.h"

typedef struct NATIVE_MODULE_HANDLE_DATA_TAG
{
    MODULE_HANDLE real_module;
    MODULE_API*   api;

}NATIVE_MODULE_HANDLE_DATA;

static MODULE_HANDLE Native_Create(BROKER_HANDLE broker, const void* configuration)
{
    NATIVE_MODULE_HANDLE_DATA* result;
    const NATIVE_MODULE_CONFIG* module_config = (NODEJS_MODULE_CONFIG*)configuration;

    if (broker == NULL || configuration == NULL)
    {
        LogError("Native_Create() - Invalid inputs - broker = %p, configuration = %p"
            broker,
            configuration
        );
        result = NULL;
    }
    else
    {
        result = (NATIVE_MODULE_HANDLE_DATA*)malloc(sizeof(NATIVE_MODULE_HANDLE_DATA));
        if (result == NULL)
        {
            LogError("Native_Create() - malloc failed");
        }
        else
        {
            result->api = module_config->real_module_api;

            // delegate to the "real" module
            result->real_module = MODULE_CREATE(result->real_module_api)(broker, module_config->configuration);
        }
    }

    return (MODULE_HANDLE)result;
}

static MODULE_HANDLE Native_CreateFromJson(BROKER_HANDLE broker, const char* configuration)
{
    MODULE_HANDLE result;

    if (module != NULL)
    {
        NATIVE_MODULE_HANDLE_DATA* native_module = (NATIVE_MODULE_HANDLE_DATA*)module;
        result = MODULE_CREATE_FROM_JSON(native_module->api)(broker, configuration);
    }
    else
    {
        LogError("Native_CreateFromJson() - module is NULL");
        result = NULL;
    }

    return result;
}

static void Native_Start(MODULE_HANDLE module)
{
    if (module != NULL)
    {
        NATIVE_MODULE_HANDLE_DATA* native_module = (NATIVE_MODULE_HANDLE_DATA*)module;
        if (MODULE_START(native_module->api) != NULL)
        {
            MODULE_START(native_module->api)(native_module->real_module);
        }
    }
    else
    {
        LogError("Native_Start() - module is NULL");
    }
}

void Native_Receive(MODULE_HANDLE module, MESSAGE_HANDLE message)
{
    if (module != NULL)
    {
        NATIVE_MODULE_HANDLE_DATA* native_module = (NATIVE_MODULE_HANDLE_DATA*)module;
        MODULE_RECEIVE(native_module->api)(native_module->real_module, message);
    }
    else
    {
        LogError("Native_Receive() - module is NULL");
    }
}

static void Native_Destroy(MODULE_HANDLE module)
{
    if (module != NULL)
    {
        NATIVE_MODULE_HANDLE_DATA* native_module = (NATIVE_MODULE_HANDLE_DATA*)module;
        MODULE_DESTROY(native_module->api)(native_module->real_module);

        free(native_module);
    }
    else
    {
        LogError("Native_Destroy() - module is NULL");
    }
}

static const MODULE_API_1 Native_APIS_all =
{
    { MODULE_API_VERSION_1 },

    Native_CreateFromJson,
    Native_Create,
    Native_Destroy,
    Native_Receive,
    Native_Start
};


MODULE_EXPORT const MODULE_API* Module_GetApi(const MODULE_API_VERSION gateway_api_version)
{
    (void)gateway_api_version;
    return reinterpret_cast< const MODULE_API *>(&Native_APIS_all);
}
