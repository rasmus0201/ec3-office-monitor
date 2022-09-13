/**
 * @file defs.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Program definitions header file
 * @version 0.1
 * @date 2020-08-20
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef BUNDSGAARD_DEFS_H

#define DEVICE_ID 1
#define NTP_SYNC_INTERVAL 10080

#define DHT_SENSOR_DELAY 5000
#define LIGHT_SENSOR_DELAY 5000
#define SOUND_SENSOR_DELAY 500

#define API_BASE_URL "http://10.130.67.71/api/v1"
#define API_TOKEN "05Cknj50fawAOaUrDDmy2158X817BNmuDlDldQmbFHtpqJ05Iq3oitxmyrh8D82F"

#define SENSOR_MANAGER_LOOP_SLEEP_TIME 5ms

#define DATA_MANAGER_LOOP_SLEEP_TIME 500ms
#define DATA_MANAGER_MAX_ITEM_BEFORE_SYNC 50

#endif
