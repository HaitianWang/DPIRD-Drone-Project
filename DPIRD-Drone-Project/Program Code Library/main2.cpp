#include <stdio.h>
#include <dji_logger.h>
#include <dji_camera_manager.h>
#include <dji_platform.h>

#define MOUNT_POSITION DJI_MOUNT_POSITION_PAYLOAD_PORT_NO1  // ??????

void InitCameraAndFetchInfo() {
    T_DjiReturnCode returnCode;
    E_DjiCameraType cameraType;
    T_DjiCameraManagerFirmwareVersion firmwareVersion;
    E_DjiCameraManagerISO isoValue;

    // **Step 1: ?????????**
    USER_LOG_INFO("--> Step 1: Init camera manager module");
    returnCode = DjiCameraManager_Init();
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("Init camera manager failed, error code: 0x%08X", returnCode);
        return;
    }

    // **Step 2: ??????**
    USER_LOG_INFO("--> Step 2: Get camera type");
    returnCode = DjiCameraManager_GetCameraType(MOUNT_POSITION, &cameraType);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("Get camera type failed, error code: 0x%08X", returnCode);
        return;
    }
    USER_LOG_INFO("Camera Type: %d", cameraType);

    // **Step 3: ????????**
    USER_LOG_INFO("--> Step 3: Get camera firmware version");
    returnCode = DjiCameraManager_GetFirmwareVersion(MOUNT_POSITION, &firmwareVersion);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        USER_LOG_ERROR("Get firmware version failed, error code: 0x%08X", returnCode);
        return;
    }
    USER_LOG_INFO("Camera Firmware: V%d.%d.%d.%d",
                  firmwareVersion.firmware_version[0], 
                  firmwareVersion.firmware_version[1], 
                  firmwareVersion.firmware_version[2], 
                  firmwareVersion.firmware_version[3]);

    // **Step 4: ???? ISO ??**
    USER_LOG_INFO("--> Step 4: Get camera ISO");
    returnCode = DjiCameraManager_GetISO(MOUNT_POSITION, &isoValue);
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS &&
        returnCode != DJI_ERROR_CAMERA_MANAGER_MODULE_CODE_UNSUPPORTED_COMMAND) {
        USER_LOG_ERROR("Get camera ISO failed, error code: 0x%08X", returnCode);
        return;
    }
    USER_LOG_INFO("Camera ISO: %d", isoValue);

    // **Step 5: ????????**
    DjiCameraManager_DeInit();
}

int main() {
    // ????????????
    InitCameraAndFetchInfo();
    return 0;
}
