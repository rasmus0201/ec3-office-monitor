#include <map>
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
}

int Collection::Size()
{
    return this->c.size();
}

float Collection::Average()
{
    float avg;

    for (auto &element : this->c) {
        avg += element.value;
    }    

    return avg/this->Size();
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
