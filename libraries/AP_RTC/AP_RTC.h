#pragma once

#include "AP_RTC_config.h"

#if AP_RTC_ENABLED

#include <AP_Param/AP_Param.h>

#include <stdint.h>

class AP_RTC {

public:

    AP_RTC();

    static const struct AP_Param::GroupInfo var_info[];

    AP_Int8 allowed_types;
    AP_Int16 tz_min;

    // ordering is important in source_type; lower-numbered is
    // considered a better time source.  These values are documented
    // and used in the parameters!
    enum source_type : uint8_t {
        SOURCE_GPS = 0,
        SOURCE_MAVLINK_SYSTEM_TIME = 1,
        SOURCE_HW = 2,
        SOURCE_NONE,
    };

    /*
      get clock in UTC microseconds.  Returns false if it is not available.
     */
    bool get_utc_usec(uint64_t &usec) const;

    // set the system time.  If the time has already been set by
    // something better (according to source_type), this set will be
    // ignored.
    void set_utc_usec(uint64_t time_utc_usec, source_type type);

    /*
      get time in UTC hours, minutes, seconds and milliseconds
     */
    bool get_system_clock_utc(uint8_t &hour, uint8_t &min, uint8_t &sec, uint16_t &ms) const;
    
    bool get_local_time(uint8_t &hour, uint8_t &min, uint8_t &sec, uint16_t &ms) const;

    uint32_t get_time_utc(int32_t hour, int32_t min, int32_t sec, int32_t ms);

    // get date and time.  Returns true on success and fills in year, month, day, hour, min, sec and ms
    // year is the regular Gregorian year, month is 0~11, day is 1~31, hour is 0~23, minute is 0~59, second is 0~60 (1 leap second), ms is 0~999
    bool get_date_and_time_utc(uint16_t& year, uint8_t& month, uint8_t& day, uint8_t &hour, uint8_t &min, uint8_t &sec, uint16_t &ms) const;

    // get singleton instance
    static AP_RTC *get_singleton() {
        return _singleton;
    }

    // allow threads to lock against RTC update
    HAL_Semaphore &get_semaphore(void) {
        return rsem;
    }

    bool clock_s_to_date_fields(const uint32_t utc_sec32, uint16_t& year, uint8_t& month, uint8_t& day, uint8_t &hour, uint8_t &min, uint8_t &sec, uint8_t &wday) const;
    uint32_t date_fields_to_clock_s(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) const;

private:

    static AP_RTC *_singleton;
    HAL_Semaphore rsem;

    source_type rtc_source_type = SOURCE_NONE;
    int64_t rtc_shift;

    void clock_ms_to_hms_fields(const uint64_t time_ms, uint8_t &hour, uint8_t &min, uint8_t &sec, uint16_t &ms) const;

    static bool _is_leap(uint32_t y);
    static uint32_t _timegm(struct tm &tm);
};

namespace AP {
    AP_RTC &rtc();
};

#endif  // AP_RTC_ENABLED
