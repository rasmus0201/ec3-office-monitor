#include <string>
#include "SoundSensor.h"
#include "CollectionElement.h"

using namespace Bundsgaard;

SoundSensor::SoundSensor(PinName pin, int sleep) : sensor(pin)
{
    this->sleepFor = std::chrono::milliseconds(sleep);
}

bool SoundSensor::Run(DataManager* manager)
{
    if (NULL != this->sensorManager->GetSensorIdFromName("sound")) {
        CollectionElement el;
        el.sensorId = this->sensorManager->GetSensorIdFromName("sound");
        el.timestamp = manager->GetRtc()->GetTimestampMS();
        el.value = (float)sensor.read_u16();
        manager->dataStore->Push(el);
    }

    return true;
}

std::chrono::milliseconds SoundSensor::GetSleepTimeout()
{
    return this->sleepFor;
}
