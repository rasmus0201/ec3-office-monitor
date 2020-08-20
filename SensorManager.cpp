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

        int i = 0;
        for (auto &sensor : this->sensorsIn) {
            if (currentMillis - prevMillisArr[i] >= sensor->GetSleepTimeout().count()) {
                if (sensor->Run(this->dataManager)) {
                    printf("%llu: Sensor %s run was good\n", currentMillis, sensor->GetName().c_str());
                    prevMillisArr[i] = currentMillis;
                }
            }

            i++;
        }

        ThisThread::sleep_for(1ms);
    }
}

std::vector<SensorInterface*>* SensorManager::GetSensorsIn()
{
    return &this->sensorsIn;
}
