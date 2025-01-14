#pragma once

#include "RGBLed.h"

#if AP_NOTIFY_RCOUTPUTRGBLED_LED_ENABLED
class RCOutputRGBLed: public RGBLed {
public:
    RCOutputRGBLed(uint8_t red_channel, uint8_t green_channel,
                   uint8_t blue_channel, uint8_t led_off, uint8_t led_full,
                   uint8_t led_medium, uint8_t led_dim);
    RCOutputRGBLed(uint8_t red_channel, uint8_t green_channel,
                   uint8_t blue_channel);
    bool init() override;

protected:
    virtual bool hw_set_rgb(uint8_t red, uint8_t green, uint8_t blue) override;
    virtual uint16_t get_duty_cycle_for_color(const uint8_t color, const uint16_t usec_period) const;

private:
    uint8_t _red_channel;
    uint8_t _green_channel;
    uint8_t _blue_channel;
};
#endif  // AP_NOTIFY_RCOUTPUTRGBLED_LED_ENABLED

#if AP_NOTIFY_RCOUTPUTRGBLEDINVERTED_LED_ENABLED
class RCOutputRGBLedInverted : public RCOutputRGBLed {
public:
    RCOutputRGBLedInverted(uint8_t red_channel, uint8_t green_channel, uint8_t blue_channel)
        : RCOutputRGBLed(red_channel, green_channel, blue_channel)
    { }
protected:
    virtual uint16_t get_duty_cycle_for_color(const uint8_t color, const uint16_t usec_period) const override;
};
#endif  // AP_NOTIFY_RCOUTPUTRGBLEDINVERTED_LED_ENABLED

#if AP_NOTIFY_RCOUTPUTRGBLEDOFF_LED_ENABLED
class RCOutputRGBLedOff : public RCOutputRGBLed {
public:
    RCOutputRGBLedOff(uint8_t red_channel, uint8_t green_channel,
                      uint8_t blue_channel, uint8_t led_off)
        : RCOutputRGBLed(red_channel, green_channel, blue_channel,
                         led_off, led_off, led_off, led_off)
    { }

    /* Override the hw_set_rgb method to turn leds off regardless of the
     * values passed */
    bool hw_set_rgb(uint8_t red, uint8_t green, uint8_t blue) override
    {
        return RCOutputRGBLed::hw_set_rgb(_led_off, _led_off, _led_off);
    }
};
#endif  // AP_NOTIFY_RCOUTPUTRGBLEDOFF_LED_ENABLED
