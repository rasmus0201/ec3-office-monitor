/**
 * @file Collection.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Collection header file
 * @version 0.1
 * @date 2020-08-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef BUNDSGAARD_COLLECTION_H
#define BUNDSGAARD_COLLECTION_H

#include <map>
#include <vector>
#include <string>
#include "CollectionElement.h"

using namespace Bundsgaard;

namespace Bundsgaard
{
    /**
     * @brief A generic collection to hold collection elements
     * 
     */
    class Collection
    {
        public:
            /**
             * @brief Push a new element to the vector (array)
             * 
             * @param value 
             */
            void Push(CollectionElement value);

            /**
             * @brief Clears the internal vector also handles
             *        shrinking of vector for memory performance.
             * 
             */
            void Clear();

            /**
             * @brief Get the number of element in collection
             * 
             * @return int 
             */
            int Size();

            /**
             * @brief Get the collections keys (unique)
             * 
             * @return vector<std::string>
             */
            vector<std::string> Keys();

            /**
             * @brief Get the average of the collection elements's value
             * 
             * @param key
             * 
             * @return float 
             */
            float Average(std::string key);

            /**
             * @brief Get the collection as a JSON string
             * 
             * @return std::string 
             */
            std::string ToJson();

        private:
            std::vector<CollectionElement> c;
    };
}

#endif
