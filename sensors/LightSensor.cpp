#include <string>
#include "LightSensor.h"
#include "CollectionElement.h"
#include "SensorManager.h"

using namespace Bundsgaard;

LightSensor::LightSensor(SensorManager* sensorManager, PinName pin, int sleep) : sensor(pin)
{
    this->sensorManager = sensorManager;
    this->sleepFor = std::chrono::milliseconds(sleep);
}

bool LightSensor::Run(DataManager* manager)
{
    if (this->sensorManager->IsSensorEnabled("light")) {
        CollectionElement el;
        el.type = "light";
        el.timestamp = manager->GetRtc()->GetTimestampMS();
        el.value = (float)sensor.read_u16();
        manager->dataStore->Push(el);
    }

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
