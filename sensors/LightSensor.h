#ifndef BUNDSGAARD_LIGHT_SENSOR_H
#define BUNDSGAARD_LIGHT_SENSOR_H

#include <string>
#include "mbed.h"
#include "SensorInterface.h"
#include "DataManager.h"

using namespace Bundsgaard;

namespace Bundsgaard
{
    class LightSensor : public SensorInterface
    {
        public:
            LightSensor(PinName pin, int sleep);
            bool Run(DataManager *manager);
            void SetName(std::string name);
            std::string GetName();

        private:
            AnalogIn sensor;
            
            std::string name;
            std::chrono::milliseconds sleepFor;
    };
}

#endif
