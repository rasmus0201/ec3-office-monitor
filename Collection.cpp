#include <vector>
#include <algorithm>
#include <string>
#include "Collection.h"
#include "CollectionElement.h"

using namespace Bundsgaard;

void Collection::Push(CollectionElement value)
{
    this->c[value.type].push_back(value);

    if (this->c.at(value.type).size() >= this->maxSubelements) {
        this->c.at(value.type).erase(
            this->c.at(value.type).begin(),
            this->c.at(value.type).begin() + (this->c.at(value.type).size() - this->keepSubelements)
        );
    }
}

void Collection::Clear()
{
    std::vector<std::string> keys = this->Keys();
    for (auto &k : keys) {
        this->c[k].clear();
    }

    this->c.clear();
}

int Collection::Size()
{
    int size = 0;

    for (auto &v : this->c) {
        size += v.second.size();
    }

    return size;
}

vector<std::string> Collection::Keys()
{
    vector<std::string> keys;

    for (auto &element : this->c) {
        keys.push_back(element.first);
    }

    std::sort(keys.begin(), keys.end());

    return keys;
}

float Collection::Average(std::string key)
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
