#ifndef BUNDSGAARD_SOUND_SENSOR_H
#define BUNDSGAARD_SOUND_SENSOR_H

#include <string>
#include "mbed.h"
#include "SensorInterface.h"
#include "DataManager.h" 

using namespace Bundsgaard;

namespace Bundsgaard
{
    class SoundSensor : public SensorInterface
    {
        public:
            SoundSensor(PinName pin, int sleep);
            bool Run(DataManager* manager);
            void SetName(std::string name);
            std::string GetName();
            uint64_t GetSleepTimeout();

        private:
            AnalogIn sensor;
    };
}

#endif
