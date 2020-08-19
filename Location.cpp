#include <string>
#include "Location.h"

using namespace std;
using namespace Bundsgaard;

Location::Location(int deviceId)
{
    this->deviceId = deviceId;
}

void Location::SetBuilding(string str)
{
    this->building = str;
}

string Location::GetBuilding()
{
    return this->building;
}

void Location::SetRoom(string str)
{
    this->room = str;
}

string Location::GetRoom()
{
    return this->room;
}

string Location::ToJson()
{
    string json = "{";

    // Building
    json += "\"building\":";
    json += "\"";
    json += this->building;
    json += "\"";

    json += ",";

    // Room
    json += "\"room\":";
    json += "\"";
    json += this->room;
    json += "\"";

    json += "}";

    return json;
}
