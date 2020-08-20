#include <string>
#include "mbed.h"
#include "Rtc.h"
#include "http_request.h"
#include "defs.h"
#include "Collection.h"
#include "DataManager.h"

using namespace Bundsgaard;

DataManager::DataManager(Rtc* rtc)
{
    this->apiUrl = "http://ec2-api.rasmusbundsgaard.dk/api/v1/sensors";
    this->Setup();
    this->rtc = rtc;
    this->dataStore = new Collection();
    this->thread.start(callback(this, &DataManager::Worker));
}

Rtc* DataManager::GetRtc()
{
    return this->rtc;
}

void DataManager::Setup()
{
    this->net = NetworkInterface::get_default_instance();

    // Connect to network if not connected
    if (this->net->get_connection_status() == NSAPI_STATUS_DISCONNECTED) {
        nsapi_size_or_error_t result = this->net->connect();
        if (result != 0) {
            printf("Error! net->connect() returned: %d\n", result);
            return;
        }
    }

    // Set the TCP socket to use
    // across HTTP request to save memory
    this->socket = new TCPSocket();

    if (this->socket->open(this->net) != NSAPI_ERROR_OK) {
        printf("TCPSocket not opened!\n");
        return;
    }

    SocketAddress addr;
    ParsedUrl* parsed_url = new ParsedUrl(this->apiUrl.c_str());
    if (this->net->gethostbyname(parsed_url->host(), &addr) != NSAPI_ERROR_OK) {
        printf("Could not get the ip of host!\n");
        return;
    }

    // Connect to the website's IP with the port (http=80, https=443)
    addr.set_port(parsed_url->port());
    if (this->socket->connect(addr) != NSAPI_ERROR_OK) {
        printf("TCPSocket could not connect to address!\n");
        return;
    }

    // Cleanup
    delete parsed_url;
}

void DataManager::Worker()
{
    while (true) {
        // When the datastore becomes big enough - push it to the cloud
        if (this->dataStore->Size() >= 25) {
            this->PushToCloud();
        }

        // We don't need to have this thread active all the time
        // So a delay to optimize timing for e.g. the sensor thread.
        ThisThread::sleep_for(500ms);
    }
}

void DataManager::PushToCloud()
{
    printf("Pushing to cloud!\n");

    // Construct the request body as JSON formatted string
    std::string json = "{\"data\":";
    json += this->dataStore->ToJson();
    json += ",\"deviceId\":"+std::to_string(DEVICE_ID);
    json += "}";
    char* body = new char[json.size() + 1];
	strcpy(body, json.c_str());

    // Do an API request
    {
        HttpRequest* post_req = new HttpRequest(this->net, this->socket, HTTP_POST, this->apiUrl.c_str());
        post_req->set_header("Content-Type", "application/json");
        
        if (post_req->send(body, strlen(body))) {
            printf("Did push to cloud!\n");
        } else {
            nsapi_error_t err = post_req->get_error();
            printf("HttpRequest failed (error code %d)\n", err);

            // The request failed, so something really bad must have happened or is about to
            // To make the EC always run, we restart the program here.
            // There could be a better way of doing this, but this is the fastest solution atm. 
            NVIC_SystemReset();
        }
    }

    // Clear the datastore 
    this->dataStore->Clear();
    delete[] body;

    return;
}
