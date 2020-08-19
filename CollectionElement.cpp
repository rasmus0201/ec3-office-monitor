#include <string>
#include "CollectionElement.h"

using namespace Bundsgaard;

std::string CollectionElement::ToJson()
{
    std::string json;

    json += "{";
    json += "\"timestamp\":" + std::to_string(this->timestamp) + ",";
    json += "\"type\":\"" + this->type + "\",";
    json += "\"value\":" + std::to_string(this->value);
    json += "}";

    return json;
}
