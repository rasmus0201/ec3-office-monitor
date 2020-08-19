#ifndef BUNDSGAARD_LOCATION_H
#define BUNDSGAARD_LOCATION_H

#include <string>

namespace Bundsgaard
{
    class Location
    {
        public:
            Location(int deviceId);
            void SetBuilding(std::string str);
            std::string GetBuilding();
            void SetRoom(std::string str);
            std::string GetRoom();

            std::string ToJson();
        
        private:
            int deviceId;
            std::string building;
            std::string room;
    };
}

#endif
