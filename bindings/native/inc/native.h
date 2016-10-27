// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef NATIVE_H
#define NATIVE_H

#include "module.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct NATIVE_MODULE_CONFIG_TAG
{
    MODULE_API* real_module_api;
    const void* configuration;
} NATIVE_MODULE_CONFIG;

MODULE_EXPORT const MODULE_API* MODULE_STATIC_GETAPI(NATIVE_MODULE)(const MODULE_API_VERSION gateway_api_version);

#ifdef __cplusplus
}
#endif

#endif /*NATIVE_H*/
