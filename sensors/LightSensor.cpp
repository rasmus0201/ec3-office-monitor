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
    // CollectionElement el;
    // el.type = "light";
    // el.timestamp = manager->GetRtc()->GetTimestampMS();
    // el.value = (float)sensor.read_u16();
    // manager->dataStore->Push(el);

    return true;
}

void LightSensor::SetName(string name) {
    this->name = name;
}

string LightSensor::GetName() {
    return this->name;
}

uint64_t LightSensor::GetSleepTimeout() {
    printf("LightSensor::GetSleepTimeout = %llu\n", this->sleepFor.count());
    return this->sleepFor.count();
}
