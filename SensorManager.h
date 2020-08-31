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
#include "Collection.h"
#include "SensorInterface.h"
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
             * @brief Get the sensors
             * 
             * @return std::vector<SensorInterface*>
             */
            std::vector<SensorInterface*> GetSensors();

            /**
             * @brief Get the underlying data collection
             * 
             * @return Collection*
             */
            Collection* GetDataCollection();

        private:
            Thread thread;
            DataManager* dataManager;
            std::vector<SensorInterface*> sensors;
    };
}

#endif
