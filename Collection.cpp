#include <vector>
#include <algorithm>
#include <string>
#include "Collection.h"
#include "CollectionElement.h"

using namespace Bundsgaard;

void Collection::Push(CollectionElement value)
{
    this->c[value.type].push_back(value);
    
    if (this->c[value.type].size() >= this->maxSubelements) {
        this->c[value.type].erase(
            this->c[value.type].begin(),
            this->c[value.type].begin()+this->keepSubelements
        );
    }
}

void Collection::Clear()
{
    this->c.clear();
}

int Collection::Size()
{
    return this->c.size();
}

vector<std::string> Collection::Keys()
{
    vector<std::string> keys;

    for (auto &element : this->c) {
        keys.push_back(element.first);
    }

    return keys;
}

float Collection::Average(std::string key)
{
    int size = 0;
    float avg = 0;

    for (auto &element : this->c) {
        if (element.type != key) {
            continue;
        }

        avg += element.value;
        size++;
    }

    if (size == 0) {
        return 0;
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
