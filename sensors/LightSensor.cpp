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
    CollectionElement el;
    el.type = "light";
    el.timestamp = manager->GetRtc()->GetTimestampMS();
    el.value = (float)sensor.read_u16();
    manager->dataStore->Push(el);

    return true;
}

void LightSensor::SetName(std::string name) {
    this->name = name;
}

std::string LightSensor::GetName() {
    return this->name;
}

std::chrono::milliseconds LightSensor::GetSleepTimeout()
{
    return this->sleepFor;
}
