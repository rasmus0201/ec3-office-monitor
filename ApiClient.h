/**
 * @file ApiClient.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief ApiClient header file
 * @version 0.1
 * @date 2020-08-20
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef BUNDSGAARD_API_CLIENT_H
#define BUNDSGAARD_API_CLIENT_H

#include <map>
#include <vector>
#include <string>
#include "http_request.h"

namespace Bundsgaard
{
    /**
     * @brief An API client for HTTP comm.
     *
     */
    class ApiClient
    {
        public:
            /**
             * @brief Construct object
             */
            ApiClient();

            /**
             * @brief Destruct object
             */
            ~ApiClient();

            /**
             * @brief Create a new GET request and get response
             */
            HttpResponse* Get(std::string endpoint);

            /**
             * @brief Create a new POST request and get response
             */
            HttpResponse* Post(std::string endpoint, std::string body);

        private:
            NetworkInterface *net;
            TCPSocket *socket;
    };
}

#endif
