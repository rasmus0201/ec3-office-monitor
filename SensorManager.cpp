#include <vector>
#include <map>
#include <string>
#include "Collection.h"
#include "defs.h"
#include "SensorInterface.h"
#include "DataManager.h"
#include "SensorManager.h"

using namespace Bundsgaard;

SensorManager::SensorManager(DataManager* manager)
{
    this->dataManager = manager;
    this->sensorIds = map<string, uint32_t>();
}

bool SensorManager::SetSensorId(string key, uint32_t value)
{
    return this->sensorIds.insert(make_pair(
        key,
        value
    )).second;
}

string SensorManager::GetSensorNameFromId(uint32_t sensorId)
{
    for (auto const &entry : this->sensorIds)
    {
        if (entry.second == sensorId) {
            return entry.first;
        }
    }

    return string("");
}

uint32_t SensorManager::GetSensorIdFromName(string name)
{
    // for (auto const &entry : this->sensorIds)
    // {
    //     printf("K: , Name: %s, V: %d\n", name.c_str(), entry.second);
    // }

    // for (auto const &entry : this->sensorIds)
    // {
    //     printf("K: %s, Name: %s, V: %d\n", entry.first.c_str(), name.c_str(), entry.second);
    //     if (name.compare(entry.first) == 0) {
    //         printf("wuuuuh");
    //         return entry.second;
    //     }
    // }

    // if (this->sensorIds.find(name) == this->sensorIds.end()) {
    //     printf("Did not find: %s\n", name.c_str());
    // }

    return 3;

    // printf("In GetSensorIdFromName\n");
    
    // auto pos = this->sensorIds.find("light");
    // if (pos == this->sensorIds.end()) {
    //     printf("Not found\n");
    // } else {
    //     printf("found: %d\n", pos->second);
    // }

    // return 3;

    // if (this->sensorIds.count(name) == 0) {
    //     printf("Well shit...");
    //     return 0;
    // }

    // return this->sensorIds[name];
}

void SensorManager::AddSensor(SensorInterface* sensor)
{
    this->sensors.push_back(sensor);
}

void SensorManager::Run()
{
    this->thread.start(callback(this, &SensorManager::Work));
}

void SensorManager::Work()
{
    uint64_t currentMillis = 0;
    uint64_t prevMillisArr[this->sensors.size()];

    // Init array to all 0's
    for(int i = 0; i < this->sensors.size(); i++) {
        prevMillisArr[i] = 0;
    }

    while(true) {
        currentMillis = this->dataManager->GetRtc()->GetTimestampMS();

        int i = 0;
        for (auto &sensor : this->sensors) {
            // If the difference between now and the sensor's previous run-time is
            // greater than it's run-interval then it is eligable to run again
            if ((currentMillis - prevMillisArr[i]) >= sensor->GetSleepTimeout().count()) {
                if (sensor->Run(this->dataManager)) {
                    prevMillisArr[i] = currentMillis;
                }
            }

            i++;
        }

        // Small thread delay
        ThisThread::sleep_for(SENSOR_MANAGER_LOOP_SLEEP_TIME);
    }
}

vector<SensorInterface*> SensorManager::GetSensors()
{
    return this->sensors;
}

Collection* SensorManager::GetDataCollection()
{
    return this->dataManager->dataStore;
}
