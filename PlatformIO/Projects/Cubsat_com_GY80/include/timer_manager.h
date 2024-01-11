#ifndef TIMER_MANAGER_H
    #define TIMER_MANAGER_H

    #include <Arduino.h>
    
    void resumeTimer(HardwareTimer *timer);
    void pauseTimer(HardwareTimer *timer);
    void setTimerOverflow(HardwareTimer *timer, uint32_t frequency, callback_function_t periodCallback = nullptr);
    void configurePWM(HardwareTimer *timer, uint32_t channel, uint32_t pin, uint32_t frequency);
    void setPWM(HardwareTimer *timer, uint32_t channel, uint8_t dutycicle);
    void stopPWM(HardwareTimer *timer, uint32_t channel);

#endif
