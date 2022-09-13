/**
 * @file SoundSensor.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Sound sensor header file
 * @version 0.1
 * @date 2020-08-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef BUNDSGAARD_SOUND_SENSOR_H
#define BUNDSGAARD_SOUND_SENSOR_H

#include <string>
#include "mbed.h"
#include "SensorInterface.h"
#include "DataManager.h"
#include "SensorManager.h"

using namespace Bundsgaard;

namespace Bundsgaard
{
    /**
     * @brief Used to get the sound sensor values
     * 
     */
    class SoundSensor : public SensorInterface
    {
        public:
            /**
             * @brief Construct a new Sound Sensor object
             * 
             * @param sensorManager
             * @param pin 
             * @param sleep 
             */
            SoundSensor(SensorManager* sensorManager, PinName pin, int sleep);

            /**
             * @brief Run the data collecting for sound sensor
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
