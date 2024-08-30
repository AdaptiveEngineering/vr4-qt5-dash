#ifndef CONFIG_H
#define CONFIG_H

#define DASH_POWER_TIMEOUT 1000 * 30 // 30 seconds to hold power

#define CAN_DEVICE "can0"
#define CAN_BAUD 1000000
#define CAN_STATE_POLL_RATE 1000 * 2 // Every 2 seconds

#define GPIO_POLL_RATE 1000 / 2 // 2 times per second (where there's no interrupt)

#define FAULT_CODE_TIMEOUT 2000 * 10 // 20 seconds

#define DASH_UPDATE_RATE 1000 / 10 // 60 times per second

#endif // CONFIG_H
