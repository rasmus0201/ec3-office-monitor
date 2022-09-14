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

    if (this->socket->open(this->net) != NSAPI_ERROR_OK) {
        printf("TCPSocket not opened!\n");
        return;
    }

    SocketAddress addr;
    ParsedUrl *parsed_url = new ParsedUrl(API_BASE_URL);
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

ApiClient::~ApiClient()
{
    delete this->net;
    delete this->socket;
}

ApiResponse ApiClient::Get(std::string endpoint)
{
    HttpRequest request(
        this->net,
        this->socket,
        HTTP_GET,
        (API_BASE_URL + endpoint).c_str()
    );

    request.set_header("Content-Type", "application/json");
    request.set_header("Authorization", API_TOKEN);

    // Cleaned by request destructor
    HttpResponse* response = request.send();

    struct ApiResponse ret = {
        .success = request.get_error() == NSAPI_ERROR_OK,
        .error = request.get_error(),
        .code = response->get_status_code(),
        .body = response->get_body_as_string().c_str(),
    };

    return ret;
}

ApiResponse ApiClient::Post(std::string endpoint, std::string body)
{
    HttpRequest request(
        this->net,
        this->socket,
        HTTP_POST,
        (API_BASE_URL + endpoint).c_str()
    );

    request.set_header("Content-Type", "application/json");
    request.set_header("Authorization", API_TOKEN);

    char* contents = new char[body.size() + 1];
    strcpy(contents, body.c_str());

    // Cleaned by request destructor
    HttpResponse* response = request.send(contents, strlen(contents));

    struct ApiResponse ret = {
        .success = request.get_error() == NSAPI_ERROR_OK,
        .error = request.get_error(),
        .code = response->get_status_code(),
        .body = response->get_body_as_string(),
    };

    delete[] contents;

    return ret;
}
