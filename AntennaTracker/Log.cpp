#include "Tracker.h"

#if HAL_LOGGING_ENABLED

// Code to Write and Read packets from AP_Logger log memory

// Write an attitude packet
void Tracker::Log_Write_Attitude()
{
    const Vector3f targets{0.0f, nav_status.pitch, nav_status.bearing};
    ahrs.Write_Attitude(targets);
    AP::ahrs().Log_Write();
}

struct PACKED log_Vehicle_Baro {
    LOG_PACKET_HEADER;
    uint64_t time_us;
    float    press;
    float    alt_diff;
};

// Write a vehicle baro packet
void Tracker::Log_Write_Vehicle_Baro(float pressure, float altitude)
{
    struct log_Vehicle_Baro pkt = {
        LOG_PACKET_HEADER_INIT(LOG_V_BAR_MSG),
        time_us         : AP_HAL::micros64(),
        press           : pressure,
        alt_diff        : altitude
    };
    logger.WriteBlock(&pkt, sizeof(pkt));
}

struct PACKED log_Vehicle_Pos {
    LOG_PACKET_HEADER;
    uint64_t time_us;
    int32_t vehicle_lat;
    int32_t vehicle_lng;
    int32_t vehicle_alt;
    float vehicle_vel_x;
    float vehicle_vel_y;
    float vehicle_vel_z;
};

// Write a vehicle pos packet
void Tracker::Log_Write_Vehicle_Pos(int32_t lat, int32_t lng, int32_t alt, const Vector3f& vel)
{
    struct log_Vehicle_Pos pkt = {
        LOG_PACKET_HEADER_INIT(LOG_V_POS_MSG),
        time_us         : AP_HAL::micros64(),
        vehicle_lat     : lat,
        vehicle_lng     : lng,
        vehicle_alt     : alt,
        vehicle_vel_x   : vel.x,
        vehicle_vel_y   : vel.y,
        vehicle_vel_z   : vel.z,
    };
    logger.WriteBlock(&pkt, sizeof(pkt));
}

// @LoggerMessage: VBAR
// @Description: Information received from tracked vehicle; barometer data
// @Field: TimeUS: Time since system startup
// @Field: Press: vehicle barometric pressure
// @Field: AltDiff: altitude difference based on difference on barometric pressure

// @LoggerMessage: VPOS
// @Description: Information received from tracked vehicle; barometer position data
// @Field: TimeUS: Time since system startup
// @Field: Lat: tracked vehicle latitude
// @Field: Lng: tracked vehicle longitude
// @Field: Alt: tracked vehicle altitude
// @Field: VelX: tracked vehicle velocity, latitude component
// @Field: VelY: tracked vehicle velocity, longitude component
// @Field: VelZ: tracked vehicle velocity, vertical component, down

// type and unit information can be found in
// libraries/AP_Logger/Logstructure.h; search for "log_Units" for
// units and "Format characters" for field type information
const struct LogStructure Tracker::log_structure[] = {
    LOG_COMMON_STRUCTURES,
    {LOG_V_BAR_MSG, sizeof(log_Vehicle_Baro),
        "VBAR", "Qff", "TimeUS,Press,AltDiff", "sPm", "F00" , true },
    {LOG_V_POS_MSG, sizeof(log_Vehicle_Pos),
       "VPOS", "QLLefff", "TimeUS,Lat,Lng,Alt,VelX,VelY,VelZ", "sddmnnn", "FGGB000", true }
};

uint8_t Tracker::get_num_log_structures() const
{
    return ARRAY_SIZE(log_structure);
}

void Tracker::Log_Write_Vehicle_Startup_Messages()
{
    logger.Write_Mode((uint8_t)mode->number(), ModeReason::INITIALISED);
    gps.Write_AP_Logger_Log_Startup_messages();
}

#endif // HAL_LOGGING_ENABLED
