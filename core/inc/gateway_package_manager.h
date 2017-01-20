// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GATEWAY_PACKAGE_MANAGER_H
#define GATEWAY_PACKAGE_MANAGER_H

#ifdef __cplusplus
extern "C"
{
#endif

#define PACKAGE_MANAGER_RESULT_VALUES \
    PACKAGE_MANAGER_SUCCESS, \
    PACKAGE_MANAGER_ERROR

/**
 * @brief Enumeration describing the result of package manager APIs.
 */
DEFINE_ENUM(PACKAGE_MANAGER_RESULT, PACKAGE_MANAGER_RESULT_VALUES);

/**
 * @brief The list of supported package manager implementations.
 */
#define PACKAGE_MANAGER_TYPE_VALUES \
    UNKNOWN,    \
    NUGET,      \
    APTITUDE,   \
    NPM,        \
    MAVEN

DEFINE_ENUM(PACKAGE_MANAGER_TYPE, PACKAGE_MANAGER_TYPE_VALUES);

/**
 * @brief Captures information required to define a "package". The expectation
 *        is that all information required to uniquely define a package will be
 *        encoded in these fields.
 */
typedef struct PACKAGE_INFO_TAG
{
    const char* name;
    const char* version;
}PACKAGE_INFO;

typedef void*(*pfPackageManager_ParseConfigurationFromJson)(const char* json);

typedef void(*pfPackageManager_FreeConfiguration)(void* configuration);

typedef bool(*pfPackageManager_IsPackageInstalled)(const PACKAGE_INFO* package_info);

typedef void(*PACKAGE_MANAGER_INSTALL_CALLBACK)(
    const PACKAGE_INFO* package_info,
    PACKAGE_MANAGER_RESULT result
);

typedef PACKAGE_MANAGER_RESULT(*pfPackageManager_Configure)(void* configuration);

typedef PACKAGE_MANAGER_RESULT(*pfPackageManager_InstallPackages)(
    const VECTOR_HANDLE package_info_list,
    PACKAGE_MANAGER_INSTALL_CALLBACK callback
);

typedef struct PACKAGE_MANAGER_API_TAG
{
    /**
     * @brief Given a JSON string containing package manager specific
     *        configuration information (a custom nuget feed URL for example)
     *        this function transforms it into an internal representation that
     *        is specific to this package manager.
     */
    pfPackageManager_ParseConfigurationFromJson ParseConfigurationFromJson;

    /**
     * @brief Frees configuration information allocated by the
     *        ParseConfigurationFromJson function.
     */
    pfPackageManager_FreeConfiguration FreeConfiguration;

    /**
     * @brief Given a PACKAGE_INFO struct returns whether the package is
     *        currently installed on the gateway.
     */
    pfPackageManager_IsPackageInstalled IsPackageInstalled;

    /**
     * @brief Updates the package managers configuration with the given
     *        configuration information.
     */
    pfPackageManager_Configure Configure;

    /**
     * @brief Asynchronously installs a set of packages and invokes the
     *        callback supplied by the caller providing installation status on
     *        a per-package basis.
     */
    pfPackageManager_InstallPackages InstallPackages;

}PACKAGE_MANAGER_API;

/**
 * @brief An instance of a package manager.
 */
typedef struct PACKAGE_MANAGER_TAG
{
    PACKAGE_MANAGER_TYPE    type;
    void*                   configuration;
    PACKAGE_MANAGER_API*    api;
}PACKAGE_MANAGER;

/**
 * @brief This function creates the default set of supported package managers.
 */
PACKAGE_MANAGER_RESULT PackageManager_Initialize(void);

/**
 * @brief This function frees resources allocated during initialization.
 */
void PackageManager_DeInitialize(void);

/**
 * @brief Given a string representation of a package manager type, returns the
 *        corresponding enum value.
 */
PACKAGE_MANAGER_TYPE PackageManager_ParseType(const char* type);

/**
 * @brief Given a package manager type, retrieves a handle to it.
 */
PACKAGE_MANAGER* PackageManager_GetPackageManagerByType(PACKAGE_MANAGER_TYPE type);

#ifdef __cplusplus
}
#endif

#endif // GATEWAY_PACKAGE_MANAGER_H
