#ifndef BUNDSGAARD_DHT_SENSOR_H
#define BUNDSGAARD_DHT_SENSOR_H

#include <string>
#include "mbed.h"
#include "DHT.h"
#include "SensorInterface.h"
#include "DataManager.h"

using namespace Bundsgaard;

namespace Bundsgaard
{
    class DHTSensor : public SensorInterface
    {
        public:
            DHTSensor(PinName pin, int sleep);
            bool Run(DataManager *manager);
            void SetName(std::string name);
            std::string GetName();

        private:
            DHT sensor;

            std::string name;
            std::chrono::milliseconds sleepFor;
    };
}

#endif
