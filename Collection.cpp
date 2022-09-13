#include <vector>
#include <algorithm>
#include <string>
#include "Collection.h"
#include "CollectionElement.h"

using namespace Bundsgaard;

void Collection::Push(CollectionElement value)
{
    this->c[value.sensorId].push_back(value);
    
    if (this->c.at(value.sensorId).size() >= this->maxSubelements) {
        this->c.at(value.sensorId).erase(
            this->c.at(value.sensorId).begin(),
            this->c.at(value.sensorId).begin() + (this->c.at(value.sensorId).size() - this->keepSubelements)
        );
    }
}

void Collection::Clear()
{
    std::vector<uint32_t> keys = this->Keys();
    this->c.clear();
    
    for (auto &k : keys) {
        this->c[k].clear();
    }
}

int Collection::Size()
{
    int size = 0;
    
    for (auto &v : this->c) {
        size += v.second.size();
    }
    
    return size;
}

vector<uint32_t> Collection::Keys()
{
    vector<uint32_t> keys;

    for (auto &element : this->c) {
        keys.push_back(element.first);
    }

    std::sort(keys.begin(), keys.end());

    return keys;
}

float Collection::Average(uint32_t key)
{
    if (this->c.count(key) == 0) {
        return 0;
    }

    float avg = 0;
    int size = this->c.at(key).size();
    
    if (size == 0) {
        return 0;
    }

    for (auto &element : this->c.at(key)) {
        avg += element.value;
    }

    return avg/size;
}

std::string Collection::ToJson()
{
    std::string json;
    json += "[";

    for (auto &v : this->c) {
        for (auto &element : v.second) {
            json += element.ToJson();
            json += ",";
        }
    }
    
    json.pop_back();
    json += "]";

    return json;
}
