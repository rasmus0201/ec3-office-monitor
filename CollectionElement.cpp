#include <string>
#include "CollectionElement.h"

using namespace Bundsgaard;

std::string CollectionElement::ToJson()
{
    std::string json;

    json += "{";
    json += "\"ts\":" + std::to_string(this->timestamp) + ",";
    json += "\"t\":\"" + this->type + "\",";
    json += "\"v\":" + std::to_string(this->value);
    json += "}";

    return json;
}
