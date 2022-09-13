#include <vector>
#include <string>
#include "mbed.h"
#include "http_request.h"
#include "http_response.h"
#include "defs.h"
#include "ApiClient.h"

using namespace Bundsgaard;

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

    HttpResponse* response = req->send();

    // delete req;
    return response;
}

HttpResponse* ApiClient::Post(std::string endpoint, std::string body)
{
    string requestUrl = string(API_BASE_URL);
    requestUrl.append(endpoint);
   
    HttpRequest *req = new HttpRequest(
        this->net,
        this->socket,
        HTTP_POST,
        requestUrl.c_str()
    );

    req->set_header("Content-Type", "application/json");
    
    char* contents = new char[body.size() + 1];
    strcpy(contents, body.c_str());

    HttpResponse* response = req->send(contents, strlen(contents));

    // delete req;
    delete[] contents;

    return response;
}