#include <string>
#include "DHTSensor.h"
#include "DataManager.h"
#include "CollectionElement.h"

using namespace Bundsgaard;

DHTSensor::DHTSensor(SensorManager* sensorManager, PinName pin, int sleep) : sensor(pin, DHT22)
{
    this->sensorManager = sensorManager;
    this->sleepFor = std::chrono::milliseconds(sleep);
}

bool DHTSensor::Run(DataManager* manager)
{
    eError dhtErr = this->sensor.readData();
    if (dhtErr != eError::ERROR_NONE) {
        return false;
    }

    if (this->sensorManager->IsSensorEnabled("temperature")) {
        CollectionElement elTemp;
        elTemp.type = "temperature";
        elTemp.value = sensor.ReadTemperature(CELCIUS);
        elTemp.timestamp = manager->GetRtc()->GetTimestampMS();
        manager->dataStore->Push(elTemp);
    }

    if (this->sensorManager->IsSensorEnabled("humidity")) {
        CollectionElement elHumid;
        elHumid.type = "humidity";
        elHumid.value = sensor.ReadHumidity();
        elHumid.timestamp = manager->GetRtc()->GetTimestampMS();
        manager->dataStore->Push(elHumid);
    }

    return true;
}

void DHTSensor::SetName(std::string name) {
    this->name = name;
}

std::string DHTSensor::GetName() {
    return this->name;
}

std::chrono::milliseconds DHTSensor::GetSleepTimeout()
{
    return this->sleepFor;
}
