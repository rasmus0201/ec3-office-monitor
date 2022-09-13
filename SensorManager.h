/**
 * @file SensorManager.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Sensor manager header file
 * @version 0.1
 * @date 2020-08-20
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef BUNDSGAARD_SENSOR_MANAGER_H
#define BUNDSGAARD_SENSOR_MANAGER_H

#include <vector>
#include <map>
#include <string>
#include "Collection.h"
#include "DataManager.h"

namespace Bundsgaard
{
    /**
     * @brief Forward declaration (circular dependency)
     *
     */
    class SensorInterface;

    /**
     * @brief Used to control when the sensors collects data
     *
     */
    class SensorManager
    {
        public:
            /**
             * @brief Construct a new Sensor Manager object
             *
             * @param manager
             */
            SensorManager(DataManager* manager);

            /**
             * @brief Start/run the thread
             *
             */
            void Run();

            /**
             * @brief Thread worker
             *
             */
            void Work();

            /**
             * @brief Add a sensor to the manager, to manage
             *
             * @param sensor
             */
            void AddSensor(SensorInterface* sensor);

            /**
             * @brief Add sensor name -> ID mapping
             *
             * @param key
             * @param value
             */
            bool SetSensorId(string key, uint32_t value);

            /**
             * @brief Get sensors name from it's ID.
             *
             * @param sensorId
             */
            string GetSensorNameFromId(uint32_t sensorId);

            /**
             * @brief Get sensorId from it's name.
             *
             * @param name
             */
            uint32_t GetSensorIdFromName(string name);

            /**
             * @brief Get the sensors
             *
             * @return vector<SensorInterface*>
             */
            vector<SensorInterface*> GetSensors();

            /**
             * @brief Get the underlying data collection
             *
             * @return Collection*
             */
            Collection* GetDataCollection();

        private:
            Thread thread;
            DataManager* dataManager;
            vector<SensorInterface*> sensors;
            map<string, uint32_t> sensorIds;
    };
}

#endif
