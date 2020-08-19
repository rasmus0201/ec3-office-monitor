#include <map>
#include <string>
#include "DHTSensor.h"
#include "DataManager.h"
#include "CollectionElement.h"

using namespace Bundsgaard;

DHTSensor::DHTSensor(PinName pin, int sleep) : sensor(pin, DHT22)
{
    this->sleepFor = std::chrono::milliseconds(sleep);
}

bool DHTSensor::Run(DataManager* manager)
{
    // eError dhtErr = this->sensor.readData();

    // if (dhtErr != eError::ERROR_NONE) {
    //     return false;
    // }

    // CollectionElement elTemp;
    // elTemp.type = "temperature";
    // elTemp.value = sensor.ReadTemperature(CELCIUS);
    // elTemp.timestamp = manager->GetRtc()->GetTimestampMS();
    // manager->dataStore->Push(elTemp);

    // CollectionElement elHumid;
    // elHumid.type = "humidity";
    // elHumid.value = sensor.ReadHumidity();
    // elHumid.timestamp = manager->GetRtc()->GetTimestampMS();
    // manager->dataStore->Push(elHumid);

    return true;
}

void DHTSensor::SetName(string name) {
    this->name = name;
}

string DHTSensor::GetName() {
    return this->name;
}

uint64_t DHTSensor::GetSleepTimeout() {
    printf("DHTSensor::GetSleepTimeout = %llu\n", this->sleepFor.count());
    return this->sleepFor.count();
}