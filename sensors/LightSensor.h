/**
 * @file LightSensor.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Light sensor header file
 * @version 0.1
 * @date 2020-08-20
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef BUNDSGAARD_LIGHT_SENSOR_H
#define BUNDSGAARD_LIGHT_SENSOR_H

#include <string>
#include "mbed.h"
#include "SensorInterface.h"
#include "DataManager.h"

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
             * @param pin
             * @param sleep
             */
            LightSensor(PinName pin, int sleep);

            /**
             * @brief Run the data collecting for Light sensor
             *
             * @param manager
             * @return true
             * @return false
             */
            bool Run(DataManager *manager);

            /**
             * @brief Get the Sleep Timeout
             *
             * @return std::chrono::milliseconds
             */
            std::chrono::milliseconds GetSleepTimeout();

        private:
            AnalogIn sensor;
            std::chrono::milliseconds sleepFor;
    };
}

#endif
