/**
 * @file DHTSensor.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief DHT Sensor header file
 * @version 0.1
 * @date 2020-08-20
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef BUNDSGAARD_DHT_SENSOR_H
#define BUNDSGAARD_DHT_SENSOR_H

#include <string>
#include "mbed.h"
#include "DHT.h"
#include "SensorInterface.h"
#include "DataManager.h"
#include "SensorManager.h"

using namespace Bundsgaard;

namespace Bundsgaard
{
    /**
     * @brief Used to get the temperature and humidity values
     *
     */
    class DHTSensor : public SensorInterface
    {
        public:
            /**
             * @brief Construct a new DHTSensor object
             *
             * @param sensorManager
             * @param pin
             * @param sleep
             */
            DHTSensor(SensorManager* sensorManager, PinName pin, int sleep);

            /**
             * @brief Run the data collecting for DHT sensor
             *
             * @param manager
             * @return true
             * @return false
             */
            bool Run(DataManager *manager);

            /**
             * @brief Set the name of the sensor
             *
             * @param name
             */
            void SetName(std::string name);

            /**
             * @brief Get the name
             *
             * @return std::string
             */
            std::string GetName();

            /**
             * @brief Get the Sleep timeout
             *
             * @return std::chrono::milliseconds
             */
            std::chrono::milliseconds GetSleepTimeout();

        private:
            DHT sensor;

            std::string name;
            std::chrono::milliseconds sleepFor;
    };
}

#endif
