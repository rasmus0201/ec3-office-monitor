/**
 * @file CollectionElement.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Collection element header file
 * @version 0.1
 * @date 2022-09-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BUNDSGAARD_COLLECTION_ELEMENT_H
#define BUNDSGAARD_COLLECTION_ELEMENT_H

#include "mbed.h"
#include <string>

namespace Bundsgaard
{
    /**
     * @brief A class to hold data
     *
     */
    class CollectionElement
    {
        public:
            /**
             * @brief Get the element as a JSON string
             *
             * @return std::string
             */
            std::string ToJson();

        public:
            /**
             * @brief Type of sensor
             *
             */
            std::string type;

            /**
             * @brief The timestamp for the value
             *
             */
            uint64_t timestamp;

            /**
             * @brief Sensor value
             *
             */
            float value;
    };
}

#endif
