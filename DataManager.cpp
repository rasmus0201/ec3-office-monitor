#include <string>
#include "http_response.h"
#include "http_request.h"
#include "mbed.h"
#include "Rtc.h"
#include "defs.h"
#include "ApiClient.h"
#include "Collection.h"
#include "DataManager.h"

using namespace Bundsgaard;

DataManager::DataManager(ApiClient* apiClient, Rtc* rtc)
{
    this->dataStore = new Collection();
    this->rtc = rtc;
    this->thread.start(callback(this, &DataManager::Worker));
}

Rtc* DataManager::GetRtc()
{
    return this->rtc;
}

void DataManager::Worker()
{
    while (true) {
        // When the datastore becomes big enough - push it to the cloud
        if (this->dataStore->Size() >= DATA_MANAGER_MAX_ITEM_BEFORE_SYNC) {
            this->PushToCloud();
        }

        // We don't need to have this thread active all the time
        // So a delay to optimize timing for e.g. the sensor thread.
        ThisThread::sleep_for(DATA_MANAGER_LOOP_SLEEP_TIME);
    }
}

void DataManager::PushToCloud()
{
    printf("Pushing to cloud!\n");

    // Construct the request body as JSON formatted string
    std::string json = "{\"data\":";
    json += this->dataStore->ToJson();
    json += "}";

    // Do an API request
    {
        printf("Here1\n");
        HttpResponse* response = this->apiClient->Post(
            "/devices/" + std::to_string(DEVICE_ID) + "/measurements",
            json
        );

        if (!response) {
            printf("HttpRequest failed!\n");
            
            // The request failed, so something really bad must have happened or is about to
            // To make the EC always run, we restart the program here.
            // There could be a better way of doing this, but this is the fastest solution atm.
            NVIC_SystemReset();
            return;
        }

        printf("Did push to cloud!\n");
    }

    // Clear the datastore
    this->dataStore->Clear();
}
