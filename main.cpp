#include "main.h"

QGuiApplication *app;
QQmlApplicationEngine *engine;
QObject *dash;

unsigned char GenericDash[GenericDashFrames][GenericDashBytes];
QCanBusDevice *canDevice;
QCanBusFrame canFrame;

GpioPollerThread *gpioPoller;
ProcessingThread *processor;

QString errorMessages;
unsigned long FaultCodes[Link_ECU_Fault_Code_Count - 1];
int currentFaultCode;
unsigned long uptimeMillis;

// Process Error Messages
void processErrorMessages() {
    uptimeMillis = millis();
    errorMessages = "";
    currentFaultCode = (int)getGenericDashValue(GenericDash, ECU_FAULT_CODES_COUNT);

    if (dash->property("debugIcons").toBool()) {
        FaultCodes[currentFaultCode] = uptimeMillis + (1000 * 60 * 30); // Mute alert for 30 minutes
    } else {
        FaultCodes[currentFaultCode] = uptimeMillis;
    }

    for (int i = 1; i < Link_ECU_Fault_Code_Count - 1; i++) {
        if (currentFaultCode == 0) {
            FaultCodes[i] = 0;
        } else if (
            (FaultCodes[i] > 0) &&
            (uptimeMillis - FaultCodes[i] < FAULT_CODE_TIMEOUT)
        ) {
            errorMessages += "\nFault Code " + QString::number(i) + ": " + getLinkECUFaultCode((LinkECUFaultCodes)i);
        }
    }

    dash->setProperty("dash_ECU_FAULT_CODE_MESSAGES", errorMessages.trimmed());
}

// Process CAN frames
void processFrames() {
    while(canDevice->framesAvailable() > 0)
    {
        canFrame = canDevice->readFrame();
        if(canFrame.isValid())
        {
            switch(canFrame.frameId())
            {
            case 1000: {
                // Decode incoming Generic Dash message
                const QByteArray canPayload = canFrame.payload();
                for (unsigned char i = 0; i < sizeof(GenericDash[0]); i++)
                    GenericDash[(unsigned char)canPayload[0]][i] = canPayload[i];

                switch(canPayload[0])
                {
                case 0:
                    dash->setProperty("dash_ECU_ENGINE_SPEED_RPM", getGenericDashValue(GenericDash, ECU_ENGINE_SPEED_RPM));
                    dash->setProperty("dash_ECU_MAP_KPA", getGenericDashValue(GenericDash, ECU_MAP_KPA));
                    dash->setProperty("dash_ECU_MGP_KPA", getGenericDashValue(GenericDash, ECU_MGP_KPA));
                    break;
                case 1:
                    dash->setProperty("dash_ECU_BAROMETRIC_PRESSURE_KPA", getGenericDashValue(GenericDash, ECU_BAROMETRIC_PRESSURE_KPA));
                    dash->setProperty("dash_ECU_THROTTLE_POSITION_PERCENT", getGenericDashValue(GenericDash, ECU_THROTTLE_POSITION_PERCENT));
                    dash->setProperty("dash_ECU_INJECTOR_DUTY_CYCLE_PERCENT", getGenericDashValue(GenericDash, ECU_INJECTOR_DUTY_CYCLE_PERCENT));
                    break;
                case 2:
                    dash->setProperty("dash_ECU_SECOND_STAGE_INJECTOR_DUTY_CYCLE_PERCENT", getGenericDashValue(GenericDash, ECU_SECOND_STAGE_INJECTOR_DUTY_CYCLE_PERCENT));
                    dash->setProperty("dash_ECU_INJECTOR_PULSE_WIDTH_MS", getGenericDashValue(GenericDash, ECU_INJECTOR_PULSE_WIDTH_MS));
                    dash->setProperty("dash_ECU_ENGINE_COOLANT_TEMPERATURE_DEGREES_C", getGenericDashValue(GenericDash, ECU_ENGINE_COOLANT_TEMPERATURE_DEGREES_C));
                    break;
                case 3:
                    dash->setProperty("dash_ECU_INTAKE_AIR_TEMPERATURE_DEGRESS_C", getGenericDashValue(GenericDash, ECU_INTAKE_AIR_TEMPERATURE_DEGRESS_C));
                    dash->setProperty("dash_ECU_BATTERY_VOLTAGE", getGenericDashValue(GenericDash, ECU_BATTERY_VOLTAGE));
                    dash->setProperty("dash_ECU_MASS_AIR_FLOW_GRAMS_PER_SECOND", getGenericDashValue(GenericDash, ECU_MASS_AIR_FLOW_GRAMS_PER_SECOND));
                    break;
                case 4:
                    dash->setProperty("dash_ECU_GEAR_POSITION", getGenericDashValue(GenericDash, ECU_GEAR_POSITION));
                    dash->setProperty("dash_ECU_INJECTOR_TIMING_DEGREES", getGenericDashValue(GenericDash, ECU_INJECTOR_TIMING_DEGREES));
                    dash->setProperty("dash_ECU_IGNITION_TIMING_DEGREES", getGenericDashValue(GenericDash, ECU_IGNITION_TIMING_DEGREES));
                    break;
                case 5:
                    dash->setProperty("dash_ECU_CAM_INLET_POSITION_L_DEGREES", getGenericDashValue(GenericDash, ECU_CAM_INLET_POSITION_L_DEGREES));
                    dash->setProperty("dash_ECU_CAM_INLET_POSITION_R_DEGREES", getGenericDashValue(GenericDash, ECU_CAM_INLET_POSITION_R_DEGREES));
                    dash->setProperty("dash_ECU_CAM_EXHAUST_POSITION_L_DEGREES", getGenericDashValue(GenericDash, ECU_CAM_EXHAUST_POSITION_L_DEGREES));
                    break;
                case 6:
                    dash->setProperty("dash_ECU_CAM_EXHAUST_POSITION_R_DEGREES", getGenericDashValue(GenericDash, ECU_CAM_EXHAUST_POSITION_R_DEGREES));
                    dash->setProperty("dash_ECU_LAMBDA_1_LAMBDA", getGenericDashValue(GenericDash, ECU_LAMBDA_1_LAMBDA));
                    dash->setProperty("dash_ECU_LAMBDA_2_LAMBDA", getGenericDashValue(GenericDash, ECU_LAMBDA_2_LAMBDA));
                    break;
                case 7:
                    dash->setProperty("dash_ECU_TRIGGER_1_ERROR_COUNT", getGenericDashValue(GenericDash, ECU_TRIGGER_1_ERROR_COUNT));
                    dash->setProperty("dash_ECU_FAULT_CODES_COUNT", getGenericDashValue(GenericDash, ECU_FAULT_CODES_COUNT));
                    dash->setProperty("dash_ECU_FUEL_PRESSURE_KPA", getGenericDashValue(GenericDash, ECU_FUEL_PRESSURE_KPA));
                    break;
                case 8:
                    dash->setProperty("dash_ECU_OIL_TEMPERATURE_DEGREES_C", getGenericDashValue(GenericDash, ECU_OIL_TEMPERATURE_DEGREES_C));
                    dash->setProperty("dash_ECU_OIL_PRESSURE_KPA", getGenericDashValue(GenericDash, ECU_OIL_PRESSURE_KPA));
                    dash->setProperty("dash_ECU_LEFT_FRONT_WHEEL_SPEED_KPH", getGenericDashValue(GenericDash, ECU_LEFT_FRONT_WHEEL_SPEED_KPH));
                    break;
                case 9:
                    dash->setProperty("dash_ECU_LEFT_REAR_WHEEL_SPEED_KPH", getGenericDashValue(GenericDash, ECU_LEFT_REAR_WHEEL_SPEED_KPH));
                    dash->setProperty("dash_ECU_RIGHT_FRONT_WHEEL_SPEED_KPH", getGenericDashValue(GenericDash, ECU_RIGHT_FRONT_WHEEL_SPEED_KPH));
                    dash->setProperty("dash_ECU_RIGHT_REAR_WHEEL_SPEED_KPH", getGenericDashValue(GenericDash, ECU_RIGHT_REAR_WHEEL_SPEED_KPH));
                    break;
                case 10:
                    dash->setProperty("dash_ECU_KNOCK_LEVEL_1_COUNT", getGenericDashValue(GenericDash, ECU_KNOCK_LEVEL_1_COUNT));
                    dash->setProperty("dash_ECU_KNOCK_LEVEL_2_COUNT", getGenericDashValue(GenericDash, ECU_KNOCK_LEVEL_2_COUNT));
                    dash->setProperty("dash_ECU_KNOCK_LEVEL_3_COUNT", getGenericDashValue(GenericDash, ECU_KNOCK_LEVEL_3_COUNT));
                    break;
                case 11:
                    dash->setProperty("dash_ECU_KNOCK_LEVEL_4_COUNT", getGenericDashValue(GenericDash, ECU_KNOCK_LEVEL_4_COUNT));
                    dash->setProperty("dash_ECU_KNOCK_LEVEL_5_COUNT", getGenericDashValue(GenericDash, ECU_KNOCK_LEVEL_5_COUNT));
                    dash->setProperty("dash_ECU_KNOCK_LEVEL_6_COUNT", getGenericDashValue(GenericDash, ECU_KNOCK_LEVEL_6_COUNT));
                    break;
                case 12:
                    dash->setProperty("dash_ECU_KNOCK_LEVEL_7_COUNT", getGenericDashValue(GenericDash, ECU_KNOCK_LEVEL_7_COUNT));
                    dash->setProperty("dash_ECU_KNOCK_LEVEL_8_COUNT", getGenericDashValue(GenericDash, ECU_KNOCK_LEVEL_8_COUNT));
                    dash->setProperty("dash_ECU_LIMIT_FLAGS_BITFIELD", getGenericDashValue(GenericDash, ECU_LIMIT_FLAGS_BITFIELD));
                    break;
                default:
                    break;
                }

                break;
            }
            default:
                break;
            }
        }
    }

    // Process any error messages
    processErrorMessages();
}

void processErrors(QCanBusDevice::CanBusError error)
{
    switch (error) {
        case QCanBusDevice::ReadError:
        case QCanBusDevice::WriteError:
        case QCanBusDevice::ConnectionError:
        case QCanBusDevice::ConfigurationError:
        case QCanBusDevice::UnknownError:
            qDebug() << CAN_DEVICE << "error:" << canDevice->errorString();
            break;
        default:
            break;
    }
}

int startCan() {
    QString errorString;

    qDebug("Attempting to start SocketCAN");
    if (!QCanBus::instance()->plugins().contains("socketcan")) {
        qFatal("Error: SocketCAN plugin not available!");
        return 1;
    }

    canDevice = QCanBus::instance()->createDevice("socketcan", CAN_DEVICE, &errorString);
    if (!canDevice) {
        qFatal("CAN initialisation error: %s", qUtf8Printable(errorString));
        return 1;
    } else {
        QObject::connect(canDevice, &QCanBusDevice::framesReceived, processFrames);
        QObject::connect(canDevice, &QCanBusDevice::errorOccurred, processErrors);

        try {
            canDevice->setConfigurationParameter(QCanBusDevice::BitRateKey, CAN_BAUD);
            qDebug() << "Set" << CAN_DEVICE << "bitrate to" << CAN_BAUD << "bits per second";
        } catch (...) {
            qDebug() << "Unable to set" << CAN_DEVICE << "bitrate to" << CAN_BAUD << "bits per second";
        }

        try {
            QStringList args = {
                "link",
                "set",
                "up",
                CAN_DEVICE,
                "type",
                "can",
                "bitrate",
                QString::number(CAN_BAUD),
                "restart-ms",
                "100"
            };
            QProcess::execute("/sbin/ip", args);
        } catch (...) {
            qDebug() << "Error bringing up" << CAN_DEVICE;
            qFatal("Unable to bring up CAN BUS");
            return 1;
        }

        if (canDevice->connectDevice()) {
            qDebug() << CAN_DEVICE << "initialised";
            return 0;
        } else {
            qDebug() << "Unable to connect to" << CAN_DEVICE;
            qFatal("Unable to connect to CAN device");
            return 1;
        }
    }
}

int stopCan() {
    qDebug("Attempting to stop SocketCAN");
    if (!QCanBus::instance()->plugins().contains("socketcan")) {
        qFatal("Error: SocketCAN plugin not available!");
        return 1;
    }
    if (!canDevice) {
        qWarning("Error: can not initialised, skipping");
    }
    canDevice->disconnectDevice();
    auto canState = canDevice->state();
    if (canState == QCanBusDevice::UnconnectedState) {
        qDebug() << CAN_DEVICE << "shut down";
    } else {
        qDebug() << "Unable to disconnect from" << CAN_DEVICE << "- current state:" << canState;
        qFatal("Abnormal CAN device shutdown");
        return 1;
    }

    try {
        QStringList args = {
            "link",
            "set",
            "down",
            CAN_DEVICE
        };
        QProcess::execute("/sbin/ip", args);
        return 0;
    } catch (...) {
        qDebug() << "Error bringing down" << CAN_DEVICE;
        qFatal("Unable to bring down CAN BUS");
        return 1;
    }
}

void signalHandler(int signal)
{
    std::signal(signal, SIG_DFL);
    qDebug() << "Signal" << signal << "received, quitting application...";
    qDebug() << "Stopping CAN...";
    stopCan();
    qDebug() << "Stopping GPIO poller...";
    gpioPoller->enabled(false);
    gpioPoller->exit();
    gpioPoller->wait(2000);
    gpioPoller->terminate();
    qDebug() << "Stopping processor...";
    processor->exit();
    processor->wait(2000);
    processor->terminate();
    qDebug() << "Quitting dashboard...";
    app->quit();
}

int main(int argc, char *argv[])
{
    QGuiApplication::setSetuidAllowed(true);
    app = new QGuiApplication(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VR4.ttf");
    QFontDatabase::addApplicationFont(":/fonts/7seg.otf");
    app->setFont(QFont("DejaVu Sans"));

    // Initialise dash
    engine = new QQmlApplicationEngine();
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (component.isError()) qDebug() << "Compile errors: " << component.errors();
    dash = component.create();
    if (!dash) {
        qFatal("Unable to create dash component");
        return -1;
    }

    // Initialise GPIO
    gpioPoller = new GpioPollerThread();
    gpioPoller->start();
    gpioPoller->setPropertyContainer(dash);
    gpioPoller->enabled(true);

    // Initialise processor
    processor = new ProcessingThread();
    processor->setGpioPollerThread(gpioPoller);
    processor->start();

    // Initialise canbus
    // if (auto canRetCode = startCan()) { return canRetCode; }

    // Start QML engine
    std::signal(SIGINT,  signalHandler);
    std::signal(SIGTERM, signalHandler);
    return app->exec();
}
