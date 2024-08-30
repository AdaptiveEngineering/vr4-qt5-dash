#ifndef GPIO_H
#define GPIO_H

#include <QtGlobal>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QFile>
#include <QSocketNotifier>

#include "config.h"
#include "global.h"

struct gpioStruct {
    int pin;
    char direction[4];
    char interrupt_edge[5];
    char parameter_name[64];
};

// Our list of GPIOs we will make use of
#define GPIO_IGNITION_SW  12
#define GPIO_POWER_HOLD  25
const gpioStruct gpioList[] = {
    { GPIO_IGNITION_SW,  "in",  "both",  "gpio_IGNITION" },
    { GPIO_POWER_HOLD,   "out", "none",  "gpio_HOLD_POWER" },
};

// Other exports
#define GPIO_LOW  0
#define GPIO_HIGH 1

// Thread for GPIO interaction
class GpioPollerThread : public QThread
{
    Q_OBJECT

    private:
        void run() override;
        QObject *container;
        QHash<int, bool> gpioStates;
        bool active;
        volatile bool gpioForcePoll = false;
        unsigned long uptimeMillis, gpioPollMillis;

    public:
        // Set enabled state
        void enabled(bool state);

        // Set QObject to receive property updates
        void setPropertyContainer(QObject *obj);

        // Set GPIO state
        bool setGpioState(int pin, bool state);

        // Get GPIO state
        bool getGpioState(int pin);

        // Get all GPIO states from OS
        void getAllGpioStates();

    public slots:
        // Force a poll - for interrupts
        void forceGpioPoll();
};

#endif // GPIO_H
