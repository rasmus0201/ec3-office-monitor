#include <vector>
#include <algorithm>
#include <string>
#include "Collection.h"
#include "CollectionElement.h"

using namespace Bundsgaard;

void Collection::Push(CollectionElement value)
{
    this->c.push_back(value);
}

void Collection::Clear()
{
    this->c.clear();
    this->c.shrink_to_fit();
}

int Collection::Size()
{
    return this->c.size();
}

vector<std::string> Collection::Keys()
{
    vector<std::string> keys;

    for (auto &element : this->c) {
        keys.push_back(element.type);
    }

    std::sort(keys.begin(), keys.end());
    keys.erase(
        std::unique(keys.begin(), keys.end()),
        keys.end()
    );
    keys.shrink_to_fit();

    return keys;
}

float Collection::Average(std::string key)
{
    int size = this->Size();
    float avg = 0;

    if (size == 0) {
        return 0;
    }

    for (auto &element : this->c) {
        if (element.type == key) {
            avg += element.value;
        }
    }

    return avg/size;
}

std::string Collection::ToJson()
{
    std::string json;
    json += "[";

    for (auto &element : this->c) {
        json += element.ToJson();
        json += ",";
    }
    
    json.pop_back();
    json += "]";

    return json;
}
