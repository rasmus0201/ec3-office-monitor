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
    eError dhtErr = this->sensor.readData();
    if (dhtErr != eError::ERROR_NONE) {
        return false;
    }

    if (NULL != this->sensorManager->GetSensorIdFromName("temperature")) {
        CollectionElement elTemp;
        elTemp.sensorId = this->sensorManager->GetSensorIdFromName("temperature");
        elTemp.value = sensor.ReadTemperature(CELCIUS);
        elTemp.timestamp = manager->GetRtc()->GetTimestampMS();
        manager->dataStore->Push(elTemp);
    }

    if (NULL != this->sensorManager->GetSensorIdFromName("humidity")) {
        CollectionElement elHumid;
        elHumid.sensorId = this->sensorManager->GetSensorIdFromName("humidity");
        elHumid.value = sensor.ReadHumidity();
        elHumid.timestamp = manager->GetRtc()->GetTimestampMS();
        manager->dataStore->Push(elHumid);
    }

    return true;
}

std::chrono::milliseconds DHTSensor::GetSleepTimeout()
{
    return this->sleepFor;
}
