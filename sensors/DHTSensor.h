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
             * @param pin 
             * @param sleep 
             */
            DHTSensor(PinName pin, int sleep);

            /**
             * @brief Run the data collecting for DHT sensor
             * 
             * @param manager 
             * @return true 
             * @return false 
             */
            bool Run(DataManager *manager);

            /**
             * @brief Get the Sleep timeout
             * 
             * @return std::chrono::milliseconds 
             */
            std::chrono::milliseconds GetSleepTimeout();

        private:
            DHT sensor;
            std::chrono::milliseconds sleepFor;
    };
}

#endif
