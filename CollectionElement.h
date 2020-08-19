#ifndef BUNDSGAARD_COLLECTION_ELEMENT_H
#define BUNDSGAARD_COLLECTION_ELEMENT_H

#include "mbed.h"
#include <string>

namespace Bundsgaard
{
    class CollectionElement
    {
        public:
            std::string ToJson();

        public:
            std::string type;
            uint64_t timestamp;
            float value;
    };
}

#endif
