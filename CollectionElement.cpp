#include <string>
#include "CollectionElement.h"

using namespace Bundsgaard;

std::string CollectionElement::ToJson()
{
    std::string json;

    json += "{";
    json += "\"ts\":" + std::to_string(this->timestamp) + ",";
    json += "\"sid\":" + std::to_string(this->sensorId) + ",";
    json += "\"v\":" + std::to_string(this->value);
    json += "}";

    return json;
}
