/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "main.h"

QQmlApplicationEngine *engine;
QObject *dash;
QQmlPropertyMap dummy; // Oddly this needs to be kept
unsigned char GenericDash[GenericDashFrames][GenericDashBytes];
QCanBusDevice *can0;
QCanBusFrame canFrame;

// Process CAN frames
void processFrames() {
    while(can0->framesAvailable() > 0)
    {
        canFrame = can0->readFrame();
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
}


int main(int argc, char *argv[])
{
    QString errorString;

    QGuiApplication::setSetuidAllowed(true);
    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
    QFontDatabase::addApplicationFont(":/fonts/VR4.ttf");
    QFontDatabase::addApplicationFont(":/fonts/7seg.otf");
    app.setFont(QFont("DejaVu Sans"));

    // Initialise dash
    engine = new QQmlApplicationEngine();
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (component.isError()) qDebug() << "Compile errors: " << component.errors();
    dash = component.create();
    if (!dash) {
        qFatal("Unable to create dash component");
        return -1;
    }

    // Initialise canbus
    qDebug("Attempting to start SocketCAN");
    if (!QCanBus::instance()->plugins().contains("socketcan")) {
        qFatal("Error: SocketCAN plugin not available!");
        return -1;
    }
    can0 = QCanBus::instance()->createDevice("socketcan", "can0", &errorString);
    if (!can0) {
        qFatal("CAN initialisation error: %s", qUtf8Printable(errorString));
        return -1;
    } else {
        QObject::connect(can0, &QCanBusDevice::framesReceived, processFrames);
        if (can0->connectDevice()) {
            qDebug("CAN0 initialised");
        } else {
            qFatal("Unable to connect to CAN0");
            return -1;
        }
    }

    // if (engine->rootObjects().isEmpty()) return -1;
    return app.exec();
}
