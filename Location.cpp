#include <string>
#include "Location.h"

using namespace Bundsgaard;

void Location::SetLocationId(uint32_t id)
{
    this->locationId = id;
}

uint32_t Location::GetLocationId()
{
    return this->locationId;
}

void Location::SetLocationName(std::string str)
{
    this->locationName = str;
}

std::string Location::GetLocationName()
{
    return this->locationName;
}

void Location::SetDeviceName(std::string str)
{
    this->deviceName = str;
}

std::string Location::GetDeviceName()
{
    return this->deviceName;
}
