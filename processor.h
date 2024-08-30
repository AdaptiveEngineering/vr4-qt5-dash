#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QtGlobal>
#include <QThread>

#include "config.h"
#include "gpio.h"

// Thread for general processing
class ProcessingThread : public QThread
{
    Q_OBJECT

private:
    void run() override;
    GpioPollerThread *pt_gpioPoller;
    unsigned long pt_uptimeMillis, pt_shutdownMillis;

public:
    // Sets the GPIO poller thread
    void setGpioPollerThread(GpioPollerThread *gpioPollerThread);
};

#endif // PROCESSOR_H
