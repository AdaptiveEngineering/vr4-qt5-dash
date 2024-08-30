#include "gpio.h"

void GpioPollerThread::run() {
    // Initialise GPIOs
    for (auto gpio : gpioList) {
        // Check / ensure GPIO has been exported
        if (!checkFile(QString("/sys/class/gpio/gpio") + QString::number(gpio.pin) + QString("/value"))) {
            if (!writeFile(
                QString("/sys/class/gpio/export"),
                QByteArray(QString::number(gpio.pin).toStdString().c_str())
            )) { qFatal("Unable to export GPIO pin"); }
        }

        // Set GPIO direction
        if (!writeFile(
            QString("/sys/class/gpio/gpio") + QString::number(gpio.pin) + QString("/direction"),
            QByteArray(gpio.direction)
        )) { qFatal("Unable to set direction of GPIO pin"); }

        // Set GPIO interrupt edge if input pin
        if (strcmp(gpio.direction, "in") == 0) {
            if (!writeFile(
                QString("/sys/class/gpio/gpio") + QString::number(gpio.pin) + QString("/edge"),
                QByteArray(gpio.interrupt_edge)
            )) { qFatal("Unable to set interrupt edge of GPIO pin"); }
            QFile watchFile(QString("/sys/class/gpio/gpio") + QString::number(gpio.pin) + QString("/value"));
            QSocketNotifier notifier(watchFile.handle(), QSocketNotifier::Read);
            QObject::connect(
                &notifier,
                &QSocketNotifier::activated,
                this,
                &GpioPollerThread::forceGpioPoll
            );
        }
    }

    // Loop over reading GPIOs when required
    while (true) {
        if (active) {
            uptimeMillis = millis();
            if (gpioForcePoll || (uptimeMillis - gpioPollMillis > GPIO_POLL_RATE)) {
                this->getAllGpioStates();
                gpioPollMillis = uptimeMillis;
                gpioForcePoll = false;
            }
        }
        // Sleep for a minimum of 10 ms between poll attempts to prevent hammering CPU
        this->msleep(10);
    }
}

void GpioPollerThread::enabled(bool state) {
    active = state;
}

void GpioPollerThread::setPropertyContainer(QObject *obj) {
    container = obj;
}

bool GpioPollerThread::setGpioState(int pin, bool state) {
    return writeFile(
        QString("/sys/class/gpio/gpio") + QString::number(pin) + QString("/value"),
        QByteArray(QString::number(state).toStdString().c_str())
    );
}

bool GpioPollerThread::getGpioState(int pin) {
    return gpioStates[pin];
}

void GpioPollerThread::getAllGpioStates() {
    for (auto gpio : gpioList) {
        // Read GPIO state
        QByteArray contents;
        if (!readFile(
            QString("/sys/class/gpio/gpio") + QString::number(gpio.pin) + QString("/value"),
            contents
        )) {
            qCritical("Unable to poll GPIO");
            continue;
        }
        gpioStates[gpio.pin] = contents.startsWith(0x31) ? GPIO_HIGH : GPIO_LOW;
        qDebug() << "GPIO" << gpio.pin << "=" << gpioStates[gpio.pin];

        // Attempt to push it to external container
        try {
            container->setProperty(gpio.parameter_name, gpioStates[gpio.pin]);
        } catch(...) {
            qCritical("Unable to set container property");
        }
    }
}

void GpioPollerThread::forceGpioPoll() {
    gpioForcePoll = true;
}
