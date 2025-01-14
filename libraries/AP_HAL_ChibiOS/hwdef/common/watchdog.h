#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
  setup the watchdog
 */
void stm32_watchdog_init(void);

/*
  pat the dog, to prevent a reset. If not called for STM32_WDG_TIMEOUT_MS
  after stm32_watchdog_init() then MCU will reset
 */
void stm32_watchdog_pat(void);

/*
  return true if reboot was from a watchdog reset
 */
bool stm32_was_watchdog_reset(void);

/*
  return true if reboot was from a software reset
 */
bool stm32_was_software_reset(void);
    
/*
  save the reset reason code
 */
void stm32_watchdog_save_reason(void);

/*
  clear reset reason code
 */
void stm32_watchdog_clear_reason(void);

/*
  save persistent watchdog data
 */
void stm32_watchdog_save(const uint32_t *data, uint32_t nwords);

/*
  load persistent watchdog data
 */
void stm32_watchdog_load(uint32_t *data, uint32_t nwords);
    
#ifdef __cplusplus
}
#endif
    
