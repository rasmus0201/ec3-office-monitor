#include <string>
#include "mbed.h"
#include "mbed_mem_trace.h"
#include "http_response.h"
#include "http_request.h"
#include "Rtc.h"
#include "defs.h"
#include "ApiClient.h"
#include "Collection.h"
#include "DataManager.h"

using namespace Bundsgaard;

void print_memory_info() {
    // // allocate enough room for every thread's stack statistics
    // int cnt = osThreadGetCount();
    // mbed_stats_stack_t *stats = (mbed_stats_stack_t*) malloc(cnt * sizeof(mbed_stats_stack_t));
 
    // cnt = mbed_stats_stack_get_each(stats, cnt);
    // for (int i = 0; i < cnt; i++) {
    //     printf("Thread: 0x%X, Stack size: %u / %u\r\n", stats[i].thread_id, stats[i].max_size, stats[i].reserved_size);
    // }
    // free(stats);

    mbed_stats_heap_t heap_stats;
    mbed_stats_heap_get(&heap_stats);
    printf("Heap size: %u / %u bytes\r\n", heap_stats.current_size, heap_stats.reserved_size);
}

DataManager::DataManager(ApiClient* apiClient, Rtc* rtc)
{
    this->apiClient = apiClient;
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
    std::string json = "{\"data\":" + this->dataStore->ToJson() + "}";

    bool successful = false;

    for (int i = 0; i < 3; i++) {
        // Do an API request
        ApiResponse apiResponse = this->apiClient->Post(
            ("/devices/" + std::to_string(DEVICE_ID) + "/measurements"),
            json
        );

        // Check for errors
        if (!apiResponse.success || apiResponse.code >= 300) {
            printf("HttpRequest failed with code: %d, http status: %d\n", apiResponse.error, apiResponse.code);
            wait_us(2 * 1000 * 1000); // wait 2 seconds

            continue;
        }

        // If succesful break the loop.
        successful = true;
        break;
    }

    if (!successful) {
        // The request failed multiple times, so something really bad must have happened or is about to
        // To make the EC always run, we restart the program here.
        // There could be a better way of doing this, but this is the fastest solution atm.
        return NVIC_SystemReset();
    }

    printf("Did push to cloud!\n");

    // Clean up
    this->dataStore->Clear();

    print_memory_info();
    printf("\n");
}
