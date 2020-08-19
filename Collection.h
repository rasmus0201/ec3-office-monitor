#ifndef BUNDSGAARD_COLLECTION_H
#define BUNDSGAARD_COLLECTION_H

#include <map>
#include <vector>
#include <string>
#include "CollectionElement.h"

using namespace Bundsgaard;

namespace Bundsgaard
{
    class Collection
    {
        public:
            void Push(CollectionElement value);
            void Clear();
            int Size();
            float Average();
            std::string ToJson();

        private:
            std::vector<CollectionElement> c;
    };
}

#endif
