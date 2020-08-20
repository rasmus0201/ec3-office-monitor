/**
 * @file Location.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Location header file
 * @version 0.1
 * @date 2020-08-20
 * 
 * @copyright Copyright (c) 2020
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
             * @brief Construct a new Location object
             * 
             * @param deviceId 
             */
            Location(int deviceId);

            /**
             * @brief Set the building name
             * 
             * @param str 
             */
            void SetBuilding(std::string str);

            /**
             * @brief Get the building name
             * 
             * @return std::string 
             */
            std::string GetBuilding();

            /**
             * @brief Set the room name
             * 
             * @param str 
             */
            void SetRoom(std::string str);

            /**
             * @brief Get the room name
             * 
             * @return std::string 
             */
            std::string GetRoom();

            /**
             * @brief Get the location as a JSON formatted string
             * 
             * @return std::string 
             */
            std::string ToJson();
        
        private:
            int deviceId;
            std::string building;
            std::string room;
    };
}

#endif
