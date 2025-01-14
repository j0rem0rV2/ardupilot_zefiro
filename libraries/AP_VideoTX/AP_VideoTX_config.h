#pragma once

#include <AP_HAL/AP_HAL_Boards.h>
#include <AP_OSD/AP_OSD_config.h>

#ifndef AP_VIDEOTX_ENABLED
#define AP_VIDEOTX_ENABLED 1
#endif

#ifndef AP_TRAMP_ENABLED
#define AP_TRAMP_ENABLED AP_VIDEOTX_ENABLED && OSD_ENABLED && BOARD_FLASH_SIZE>1024
#endif

#ifndef AP_SMARTAUDIO_ENABLED
#define AP_SMARTAUDIO_ENABLED AP_VIDEOTX_ENABLED
#endif

