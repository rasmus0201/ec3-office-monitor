/**
 * @file SensorManager.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Sensor manager header file
 * @version 0.1
 * @date 2022-09-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BUNDSGAARD_SENSOR_MANAGER_H
#define BUNDSGAARD_SENSOR_MANAGER_H

#include <string>
#include <vector>
#include <map>
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
             * @brief Add sensor name -> ID mapping
             *
             * @param sensor
             */
            void EnableSensor(string sensor);

            /**
             * @brief Check if sensor is enabled.
             *
             * @param sensor
             */
            bool IsSensorEnabled(string sensor);

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

            /**
             * @brief Get the sensors (names) registered to this manager
             *
             * @return vector<string>
             */
            vector<string> GetSensorKeys();

        private:
            Thread thread;
            DataManager* dataManager;
            vector<SensorInterface*> sensors;
            map<string, bool> sensorsEnabled;
    };
}

#endif
