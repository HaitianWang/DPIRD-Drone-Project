/**
 ********************************************************************
 * @file    test_camera_manager_entry.cpp
 * @brief
 *
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

/* ????? `list[]` ??,?? PSDK ??? */
static const char *s_cameraManagerSampleSelectList[] = {
    "Shoot single photo                                  |", // ENUM: E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SHOOT_SINGLE_PHOTO
    "Record video                                        |", // ENUM: E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_RECORD_VIDEO
    "Download and delete media file                      |", // ENUM: E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_DOWNLOAD_AND_DELETE_MEDIA_FILE
    "Format SD card                                      |", // ENUM: E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_FORMAT_SD_CARD
    "Camera connect status test                          |"  // ENUM: E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_CONNECT_STATUS_TEST
};


static const E_DjiTestCameraManagerSampleSelect sampleEnumMapping[] = {
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_SHOOT_SINGLE_PHOTO,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_RECORD_VIDEO,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_DOWNLOAD_AND_DELETE_MEDIA_FILE,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_FORMAT_SD_CARD,
    E_DJI_TEST_CAMERA_MANAGER_SAMPLE_SELECT_CONNECT_STATUS_TEST
};


static void DjiTest_CmareManagerShowStringList(const char **list, int size)
{
    for (int i = 0; i < size; i++) {
        printf("| [%2d] %s\r\n", i + 1, list[i]);
    }
}


void DjiUser_RunCameraManagerSample(void)
{
    T_DjiOsalHandler *osalHandler = DjiPlatform_GetOsalHandler();
    string sampleSelectStr;
    int sampleSelectNum;
    E_DjiMountPosition cameraMountPosition = DJI_MOUNT_POSITION_PAYLOAD_PORT_NO2; // ?? NO.2 ??
    E_DjiTestCameraManagerSampleSelect cameraSample;  

    USER_LOG_INFO("Dji P1 Camera DPIRD Project");

    while (true) {
        osalHandler->TaskSleepMs(10);
        cout << "\nAvailable samples:\n";
        DjiTest_CmareManagerShowStringList(s_cameraManagerSampleSelectList, 5);

        cout << "Please input number to select sample (input q to quit): ";
        cin >> sampleSelectStr;

        if (sampleSelectStr == "q") {
            return;
        }

        sampleSelectNum = atoi(sampleSelectStr.c_str()) - 1; // ??? 1 ??

        if (sampleSelectNum < 0 || sampleSelectNum >= 5) {
            USER_LOG_ERROR("Input camera sample is invalid");
            continue;
        }


        cameraSample = sampleEnumMapping[sampleSelectNum];

        cout << "Start test: position " << cameraMountPosition
             << ", sample " << cameraSample << endl;

        DjiTest_CameraManagerRunSample(cameraMountPosition, cameraSample);
    }
}

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
