#include <stdio.h>
#include "dji_camera_manager.h"
#include "dji_typedef.h"

#define MOUNT_POSITION DJI_MOUNT_POSITION_PAYLOAD_PORT_NO1  // ????,????????

void GetCameraInfo() {
    T_DjiReturnCode returnCode;
    E_DjiCameraType cameraType;
    E_DjiCameraManagerWorkMode cameraWorkMode;  // ??????

    // ????????
    returnCode = DjiCameraManager_Init();
    if (returnCode != DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        printf("DjiCameraManager_Init failed: 0x%08X\n", returnCode);
        return;
    }

    // ??????
    returnCode = DjiCameraManager_GetCameraType(MOUNT_POSITION, &cameraType);
    if (returnCode == DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        printf("Camera Type: %d\n", cameraType);
    } else {
        printf("Failed to get Camera Type: 0x%08X\n", returnCode);
    }

    // ????????
    returnCode = DjiCameraManager_GetMode(MOUNT_POSITION, &cameraWorkMode);
    if (returnCode == DJI_ERROR_SYSTEM_MODULE_CODE_SUCCESS) {
        printf("Camera Work Mode: %d\n", cameraWorkMode);
    } else {
        printf("Failed to get Camera Work Mode: 0x%08X\n", returnCode);
    }

    // ???????
    DjiCameraManager_DeInit();
}

int main() {
    GetCameraInfo();
    return 0;
}
