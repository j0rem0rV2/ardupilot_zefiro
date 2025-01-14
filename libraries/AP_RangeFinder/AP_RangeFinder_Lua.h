#pragma once

#include "AP_RangeFinder_config.h"

#if AP_RANGEFINDER_LUA_ENABLED

#include "AP_RangeFinder_Backend.h"

// Data timeout
#define AP_RANGEFINDER_LUA_TIMEOUT_MS 500

class AP_RangeFinder_Lua : public AP_RangeFinder_Backend
{
public:

    // constructor
    AP_RangeFinder_Lua(RangeFinder::RangeFinder_State &_state, AP_RangeFinder_Params &_params);

    // update state
    void update(void) override;

    // Get update from Lua script
    bool handle_script_msg(float dist_m) override;
    bool handle_script_msg(const RangeFinder::RangeFinder_State &state_arg) override;

    MAV_DISTANCE_SENSOR _get_mav_distance_sensor_type() const override {
        return MAV_DISTANCE_SENSOR_UNKNOWN;
    }

private:

    RangeFinder::RangeFinder_State _state_pending = {};
};

#endif  // AP_RANGEFINDER_LUA_ENABLED
