#ifndef BUNDSGAARD_SENSOR_MANAGER_H
#define BUNDSGAARD_SENSOR_MANAGER_H

#include <vector>
#include "SensorInterface.h"
#include "DataManager.h"

namespace Bundsgaard
{
    class SensorInterface;

    class SensorManager
    {
        public:
            SensorManager(DataManager* manager);
            void Run();
            void Work();
            void AddSensorIn(SensorInterface* sensor);
            std::vector<SensorInterface*>* GetSensorsIn();

        private:
            Thread thread;
            DataManager* dataManager;
            std::vector<SensorInterface*> sensorsIn;
    };
}

#endif
