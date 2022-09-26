/**
 * @file Location.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Location header file
 * @version 0.1
 * @date 2022-09-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BUNDSGAARD_LOCATION_H
#define BUNDSGAARD_LOCATION_H

#include <string>

namespace Bundsgaard
{
    /**
     * @brief Set the physical location of the device
     *
     */
    class Location
    {
        public:
            /**
             * @brief Set the location ID
             *
             * @param id
             */
            void SetLocationId(uint32_t id);

            /**
             * @brief Get the location ID
             */
            uint32_t GetLocationId();

            /**
             * @brief Set the location name
             *
             * @param str
             */
            void SetLocationName(std::string str);

            /**
             * @brief Get the location name
             */
            std::string GetLocationName();

            /**
             * @brief Set the device name
             *
             * @param str
             */
            void SetDeviceName(std::string str);

            /**
             * @brief Get the device name
             */
            std::string GetDeviceName();

            /**
             * @brief Set the device timezone
             *
             * @param timezone
             */
            void SetLocationTimezone(int32_t timezone);

            /**
             * @brief Get the device timezone
             */
            int32_t GetLocationTimezone();

        private:
            uint32_t locationId;
            int32_t timezone;
            std::string locationName;
            std::string deviceName;
    };
}

#endif
