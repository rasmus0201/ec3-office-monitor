#include <vector>
#include "Collection.h"
#include "SensorInterface.h"
#include "DataManager.h"
#include "SensorManager.h"

using namespace Bundsgaard;

SensorManager::SensorManager(DataManager* manager)
{
    this->dataManager = manager;
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
            if (currentMillis - prevMillisArr[i] >= sensor->GetSleepTimeout().count()) {
                if (sensor->Run(this->dataManager)) {
                    // printf("%llu: Sensor %s run was good\n", currentMillis, sensor->GetName().c_str());
                    prevMillisArr[i] = currentMillis;
                }
            }

            i++;
        }

        // Small thread delay
        ThisThread::sleep_for(5ms);
    }
}

std::vector<SensorInterface*> SensorManager::GetSensors()
{
    return this->sensors;
}

Collection* SensorManager::GetDataCollection()
{
    return this->dataManager->dataStore;
}
