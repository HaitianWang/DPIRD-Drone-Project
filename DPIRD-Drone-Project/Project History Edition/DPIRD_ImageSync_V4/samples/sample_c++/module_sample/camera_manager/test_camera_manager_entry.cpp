/**
 ********************************************************************
 * @file    test_camera_manager_entry.cpp
 * @brief   Auto-download and delete media files from Zenmuse P1 (stable version).
 *********************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <dji_logger.h>
#include <dji_typedef.h>
#include "utils/util_misc.h"
#include "dji_camera_manager.h"
#include "camera_manager/test_camera_manager.h"
#include "camera_manager/test_camera_manager_entry.h"

using namespace std;

/**
 * @brief Format SD card before starting the download process.
 */
void FormatSDCard(E_DjiMountPosition cameraMountPosition)
{
    T_DjiReturnCode returnCode = DjiCameraManager_FormatStorage(cameraMountPosition);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("Failed to format SD card, error code: 0x%08X", returnCode);
    } else {
        USER_LOG_INFO("SD card formatted successfully.");
    }
}

/**
 * @brief Calls the original PSDK function to download and delete media files.
 */
void DownloadAndDeleteMediaFiles(E_DjiMountPosition cameraMountPosition)
{
    T_DjiReturnCode returnCode;

    USER_LOG_INFO("Downloading and deleting media files...");

    returnCode = DjiTest_CameraManagerRunSample(cameraMountPosition, 
                 E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_DOWNLOAD_AND_DELETE_MEDIA_FILE);
    
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("Failed to execute download and delete, error code: 0x%08X", returnCode);
    } else {
        USER_LOG_INFO("Download and delete completed.");
    }
}

/**
 * @brief Runs the main auto-download system.
 */
void DjiUser_RunCameraManagerSample(void)
{
    T_DjiOsalHandler *osalHandler = DjiPlatform_GetOsalHandler();
    E_DjiMountPosition cameraMountPosition = DJI_MOUNT_POSITION_PAYLOAD_PORT_NO1; 

    USER_LOG_INFO("Dji P1 Camera Auto-Sync System Started.");

    /* Initialize the camera manager module */
    T_DjiReturnCode returnCode = DjiCameraManager_Init();
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("Failed to initialize camera manager, error code: 0x%08X", returnCode);
        return;
    }

    /* Format SD card before starting */
    FormatSDCard(cameraMountPosition);

    /* Start monitoring loop */
    while (true) {
        osalHandler->TaskSleepMs(10000); // Check every 10 seconds
        DownloadAndDeleteMediaFiles(cameraMountPosition);
    }
}
