#include <string>
#include "SoundSensor.h"
#include "CollectionElement.h"
#include "SensorManager.h"

using namespace Bundsgaard;

SoundSensor::SoundSensor(SensorManager* sensorManager, PinName pin, int sleep) : sensor(pin)
{
    this->sensorManager = sensorManager;
    this->sleepFor = std::chrono::milliseconds(sleep);
}

bool SoundSensor::Run(DataManager* manager)
{
    if (this->sensorManager->IsSensorEnabled("sound")) {
        CollectionElement el;
        el.type = "sound";
        el.timestamp = manager->GetRtc()->GetTimestampMS();
        el.value = (float)sensor.read_u16();
        manager->dataStore->Push(el);
    }

    return true;
}

void SoundSensor::SetName(std::string name)
{
    this->name = name;
}

std::string SoundSensor::GetName()
{
    return this->name;
}

std::chrono::milliseconds SoundSensor::GetSleepTimeout()
{
    return this->sleepFor;
}
