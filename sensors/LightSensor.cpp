#include <string>
#include "LightSensor.h"
#include "CollectionElement.h"

using namespace Bundsgaard;

LightSensor::LightSensor(PinName pin, int sleep) : sensor(pin)
{
    this->sleepFor = std::chrono::milliseconds(sleep);
}

bool LightSensor::Run(DataManager* manager)
{
    if (NULL != this->sensorManager->GetSensorIdFromName("light")) {
        CollectionElement el;
        el.sensorId = this->sensorManager->GetSensorIdFromName("light");
        el.timestamp = manager->GetRtc()->GetTimestampMS();
        el.value = (float)sensor.read_u16();
        manager->dataStore->Push(el);
    }

    return true;
}

std::chrono::milliseconds LightSensor::GetSleepTimeout()
{
    return this->sleepFor;
}
