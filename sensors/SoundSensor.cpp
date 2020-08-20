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
    printf("SoundSensor::Run()\n");

    CollectionElement el;
    el.type = "sound";
    el.timestamp = manager->GetRtc()->GetTimestampMS();
    el.value = (float)sensor.read_u16();
    manager->dataStore->Push(el);

    return true;
}

void SoundSensor::SetName(std::string name) {
    this->name = name;
}

std::string SoundSensor::GetName() {
    return this->name;
}
