#include "processor.h"

void ProcessingThread::run() {
    while (true) {
        pt_uptimeMillis = millis();
        if (pt_gpioPoller->getGpioState(GPIO_IGNITION_SW)) {
            if (!pt_gpioPoller->getGpioState(GPIO_POWER_HOLD)) {
                pt_gpioPoller->setGpioState(GPIO_POWER_HOLD, GPIO_HIGH);
            }
            pt_shutdownMillis = pt_uptimeMillis;
        }
        else if (pt_uptimeMillis - pt_shutdownMillis > DASH_POWER_TIMEOUT) {
            pt_gpioPoller->setGpioState(GPIO_POWER_HOLD, GPIO_LOW);
        }
        this->msleep(GPIO_POLL_RATE);
    }
}

void ProcessingThread::setGpioPollerThread(GpioPollerThread *gpioPollerThread) {
    pt_gpioPoller = gpioPollerThread;
}
