#include <vector>
#include "SensorInterface.h"
#include "DataManager.h"
#include "SensorManager.h"

using namespace Bundsgaard;

SensorManager::SensorManager(DataManager* manager)
{
    this->dataManager = manager;
}

void SensorManager::AddSensorIn(SensorInterface* sensor)
{
    this->sensorsIn.push_back(sensor);
}

void SensorManager::Run()
{
    this->thread.start(callback(this, &SensorManager::Work));
}

void SensorManager::Work()
{
    uint64_t currentMillis = 0;
    uint64_t prevMillisArr[this->sensorsIn.size()];

    // Init array to all 0's
    for(int i = 0; i < this->sensorsIn.size(); i++) {
        prevMillisArr[i] = 0;
    }

    while(true) {
        currentMillis = this->dataManager->GetRtc()->GetTimestampMS();

        printf("Current millis: %llu\n", currentMillis);

        int i = 0;
        for (auto &sensor : this->sensorsIn) {
            uint64_t prevMillis = prevMillisArr[i];

            printf("Sensor i= %i, addr= %p, name= %s\n", i, (void*)sensor, sensor->GetName().c_str());
            
            // if (currentMillis - prevMillis >= sensor->GetSleepTimeout()) {
            //     prevMillisArr[i] = currentMillis;
            //     printf("Sensor %s timeout=%llu\n", sensor->GetName().c_str(), sensor->GetSleepTimeout());
            //     printf("Running for sensor... diff = %llu\n", currentMillis - prevMillis);
            //     // if (sensor->Run(this->dataManager)) {
            //     //     printf("Sensor run was good\n");
            //     //     prevMillis = currentMillis;
            //     // }
            // }

            i++;
        }

        ThisThread::sleep_for(1000ms);
    }
}

std::vector<SensorInterface*>* SensorManager::GetSensorsIn()
{
    return &this->sensorsIn;
}
