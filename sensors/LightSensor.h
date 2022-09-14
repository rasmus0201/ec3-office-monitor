/**
 * @file LightSensor.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Light sensor header file
 * @version 0.1
 * @date 2022-09-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BUNDSGAARD_LIGHT_SENSOR_H
#define BUNDSGAARD_LIGHT_SENSOR_H

#include <string>
#include "mbed.h"
#include "SensorInterface.h"
#include "DataManager.h"
#include "SensorManager.h"

using namespace Bundsgaard;

namespace Bundsgaard
{
    /**
     * @brief Used to get the light sensor values
     *
     */
    class LightSensor : public SensorInterface
    {
        public:
            /**
             * @brief Construct a new Light Sensor object
             *
             * @param sensorManager
             * @param pin
             * @param sleep
             */
            LightSensor(SensorManager* sensorManager, PinName pin, int sleep);

            /**
             * @brief Run the data collecting for Light sensor
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
             * @brief Get the sensor types this sensor is measuring.
             *
             * @return std::vector<std::string>
             */
            std::vector<std::string> GetSensorTypes();

            /**
             * @brief Get the Sleep Timeout
             *
             * @return std::chrono::milliseconds
             */
            std::chrono::milliseconds GetSleepTimeout();

        private:
            AnalogIn sensor;
            std::string name;
            std::chrono::milliseconds sleepFor;
    };
}

#endif
