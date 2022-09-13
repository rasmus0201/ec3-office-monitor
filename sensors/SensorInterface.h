/**
 * @file SensorInterface.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Sensor interface header file
 * @version 0.1
 * @date 2020-08-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef BUNDSGAARD_SENSOR_INTERFACE_H
#define BUNDSGAARD_SENSOR_INTERFACE_H

#include <string>
#include "mbed.h"
#include "DataManager.h"
#include "SensorManager.h"

namespace Bundsgaard
{
    /**
     * @brief Forward declaration (circular dependency)
     * 
     */
    class SensorManager;

    /**
     * @brief Interface for the sensors
     * 
     */
    class SensorInterface
    {
        public:
            /**
             * @brief Run the sensor
             * 
             * @param manager 
             * @return true 
             * @return false 
             */
            virtual bool Run(DataManager *manager) = 0;

            /**
             * @brief Set the name of the sensor
             * 
             * @param name 
             */
            virtual void SetName(std::string name) = 0;

            /**
             * @brief Get the name of the sensor
             * 
             * @return std::string 
             */
            virtual std::string GetName() = 0;

            /**
             * @brief Get the sleep timeout
             * 
             * @return std::chrono::milliseconds 
             */
            virtual std::chrono::milliseconds GetSleepTimeout() = 0;

        protected:
            SensorManager* sensorManager;
            std::string name;
            std::chrono::milliseconds sleepFor;
    };
}

#endif
