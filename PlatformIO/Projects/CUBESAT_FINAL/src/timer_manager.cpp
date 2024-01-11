#include "timer_manager.h"

void resumeTimer(HardwareTimer *timer){
    timer->resume();
}

void pauseTimer(HardwareTimer *timer){
    timer->pause();
}

void setTimerOverflow(HardwareTimer *timer, uint32_t frequency, callback_function_t periodCallback){
    timer->setOverflow(frequency, HERTZ_FORMAT);
    timer->attachInterrupt(periodCallback);
    timer->pause();
}

void configurePWM(HardwareTimer *timer, uint32_t channel, uint32_t pin, uint32_t frequency){
    timer->setMode(channel, TIMER_OUTPUT_COMPARE_PWM1, pin);
    timer->setOverflow(frequency, HERTZ_FORMAT);
    timer->pause();
}

void setPWM(HardwareTimer *timer, uint32_t channel, uint8_t dutycicle){
    timer->setCaptureCompare(channel, dutycicle, PERCENT_COMPARE_FORMAT);
}

void stopPWM(HardwareTimer *timer, uint32_t channel){
  timer->setCaptureCompare(channel, 0, PERCENT_COMPARE_FORMAT);
}
