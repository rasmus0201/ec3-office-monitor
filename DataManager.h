#ifndef BUNDSGAARD_DATA_MANAGER_H
#define BUNDSGAARD_DATA_MANAGER_H

#include <string>
#include "mbed.h"
#include "Rtc.h"
#include "Collection.h"

namespace Bundsgaard
{
    class DataManager
    {
        public:
            DataManager(Rtc* rtc);
            void Setup();
            void PushToCloud();
            void Worker();
            Rtc* GetRtc();
        
        public:
            Collection* dataStore;

        private:
            Rtc* rtc;
            Thread thread;
            std::string apiUrl;
            NetworkInterface* net;
            TCPSocket* socket;
    };
}

#endif
