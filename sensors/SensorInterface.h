#ifndef BUNDSGAARD_SENSOR_INTERFACE_H
#define BUNDSGAARD_SENSOR_INTERFACE_H

#include <string>
#include "mbed.h"
#include "DataManager.h"

namespace Bundsgaard
{
    class SensorManager;

    class SensorInterface
    {
        public:
            virtual bool Run(DataManager *manager) = 0;
            virtual void SetName(string name) = 0;
            virtual std::string GetName() = 0;
            virtual uint64_t GetSleepTimeout() = 0;

        protected:
            std::string name;
            std::chrono::milliseconds sleepFor;
    };
}

#endif
