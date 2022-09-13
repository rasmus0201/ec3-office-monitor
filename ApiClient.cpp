#include <vector>
#include <algorithm>
#include <string>
#include "mbed.h"
#include "http_request.h"
#include "defs.h"
#include "ApiClient.h"
#include "mbed.h"
#include "mbed_mem_trace.h"

using namespace Bundsgaard;

void print_memory_info() {
    // allocate enough room for every thread's stack statistics
    int cnt = osThreadGetCount();
    mbed_stats_stack_t *stats = (mbed_stats_stack_t*) malloc(cnt * sizeof(mbed_stats_stack_t));
 
    cnt = mbed_stats_stack_get_each(stats, cnt);
    for (int i = 0; i < cnt; i++) {
        printf("Thread: 0x%X, Stack size: %u / %u\r\n", stats[i].thread_id, stats[i].max_size, stats[i].reserved_size);
    }
    free(stats);
 
    // Grab the heap statistics
    mbed_stats_heap_t heap_stats;
    mbed_stats_heap_get(&heap_stats);
    printf("Heap size: %u / %u bytes\r\n", heap_stats.current_size, heap_stats.reserved_size);
}

ApiClient::ApiClient()
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

    if (this->socket->open(this->net) != NSAPI_ERROR_OK)
    {
        printf("TCPSocket not opened!\n");
        return;
    }

    SocketAddress addr;
    ParsedUrl *parsed_url = new ParsedUrl(API_BASE_URL);
    if (this->net->gethostbyname(parsed_url->host(), &addr) != NSAPI_ERROR_OK)
    {
        printf("Could not get the ip of host!\n");
        return;
    }

    // Connect to the website's IP with the port (http=80, https=443)
    addr.set_port(parsed_url->port());
    if (this->socket->connect(addr) != NSAPI_ERROR_OK)
    {
        printf("TCPSocket could not connect to address!\n");
        return;
    }

    // Cleanup
    delete parsed_url;
}

ApiClient::~ApiClient()
{
    delete this->net;
    delete this->socket;
}

HttpResponse* ApiClient::Get(std::string endpoint)
{
    string requestUrl = API_BASE_URL;
    requestUrl.append(endpoint);

    HttpRequest *req = new HttpRequest(
        this->net,
        this->socket,
        HTTP_GET,
        requestUrl.c_str()
    );

    req->set_header("Content-Type", "application/json");

    return req->send();
}

HttpResponse* ApiClient::Post(std::string endpoint, std::string body)
{
    print_memory_info();
    mbed_mpu_init();
    
    printf("Here2\n");
    string requestUrl = API_BASE_URL;
    requestUrl.append(endpoint);
   
    printf("Here3\n");
    HttpRequest *req = new HttpRequest(
        this->net,
        this->socket,
        HTTP_POST,
        requestUrl.c_str()
    );

    req->set_header("Content-Type", "application/json");
    
    printf("Here4\n");
    // char* contents = new char[body.size() + 1];
    // strcpy(contents, body.c_str());

    printf("%d\n", this->net->get_connection_status());
    printf("Here5\n");

    HttpResponse* response = req->send(&body.c_str() [ '\0'], body.size() + 1);

    printf("Here6\n");

    // delete[] contents;
    printf("Here7\n");

    return response;
}
