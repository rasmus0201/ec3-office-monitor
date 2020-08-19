#include <string>
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

    addr.set_port(parsed_url->port());
    if (this->socket->connect(addr) != NSAPI_ERROR_OK) {
        printf("TCPSocket could not connect to address!\n");
        return;
    }

    delete parsed_url;
}

void DataManager::Worker()
{
    while (true) {
        if (this->dataStore->Size() >= 25) {
            if (this->net->get_connection_status() == NSAPI_STATUS_DISCONNECTED) {
                nsapi_size_or_error_t result = this->net->connect();
                if (result != 0) {
                    printf("Error! net->connect() returned: %d\n", result);

                    continue;
                }
            }
            
            this->PushToCloud();
        }

        ThisThread::sleep_for(1000ms);
    }
}

void DataManager::PushToCloud()
{
    printf("Push to cloud!\n");
    std::string json = "{\"data\":";
    json += this->dataStore->ToJson();
    json += ",\"deviceId\":"+std::to_string(DEVICE_ID);
    json += "}";
    char body[json.size() + 1];
	strcpy(body, json.c_str());

    HttpRequest* post_req = new HttpRequest(this->net, this->socket, HTTP_POST, this->apiUrl.c_str());
    post_req->set_header("Content-Type", "application/json");

    HttpResponse* res = post_req->send(body, strlen(body));
    if (res) {
        this->dataStore->Clear();
        printf("Did push to cloud!\n");

        return;
    }

    nsapi_error_t err = post_req->get_error();
    printf("HttpRequest failed (error code %d)\n", err);
    if (err == NSAPI_ERROR_NO_CONNECTION) {
        this->Setup();
        return this->PushToCloud();
    }
}
