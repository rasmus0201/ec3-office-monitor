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
            bool Run(DataManager* manager);
            void SetName(string name);
            string GetName();
            uint64_t GetSleepTimeout();

        private:
            DHT sensor;
    };
}

#endif
