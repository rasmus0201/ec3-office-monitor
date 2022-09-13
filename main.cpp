/**
 * @file main.cpp
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Main file
 * @version 0.1
 * @date 2020-08-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <string>
#include "mbed.h"
#include "mbedtls_entropy_config.h"
#include "mbed_mem_trace.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "Rtc.h"
#include "defs.h"
#include "Display.h"
#include "Collection.h"
#include "Location.h"
#include "Sensors.h"
#include "SensorManager.h"


/** PINOUT
 * Led = D2
 * DHT = D4
 * Buzzer = D5
 * Button = D6
 * Sound = A0
 * Light = A1
*/

using namespace Bundsgaard;

InterruptIn button(D6);
DigitalOut led(D2);
DigitalOut buzzer(D5);

Display display;

/**
 * @brief Setup everything
 * 
 */
void setup();

/**
 * @brief Main program
 * 
 * @return int 
 */
int main()
{
    printf("Starting office monitor program\n");

    display.SetStartVariables();
    display.Setup();
    display.Clear();

    setup();

    display.Loop();

    while(true) {
        ThisThread::sleep_for(100ms);
    }
}

void setup()
{
    display.TextCentered("OFFICE MONITOR");
    display.Delay(1000);

    printf("Getting default network instance\n");
    display.Clear();
    display.TextCentered("Initializing network...");

    NetworkInterface* net = NetworkInterface::get_default_instance();

    if (!net) {
        display.Clear();
        display.FontBig();
        display.TextCentered("ERR: No ethernet connection!");
        printf("Error! No network interface found.\n");
        exit(-1);
    }

    // Connect to the network with the default networking interface
    nsapi_size_or_error_t result = net->connect();
    if (result != 0) {
        display.Clear();
        display.FontBig();
        display.TextCentered("ERR: Could not connect to internet!");
        printf("Error! net->connect() returned: %d\n", result);
        exit(-1);
    }

    printf("Setting up RTC\n");
    display.Clear();
    display.TextCentered("Setting RTC...");
    Rtc* rtc = new Rtc(NTP_SYNC_INTERVAL);
    rtc->Start();

    display.Clear();
    display.TextCentered("Initializing sensors...");

    printf("Setting up data manager\n");
    DataManager* dataManager = new DataManager(rtc);

    printf("Setting up sensor manager\n");
    SensorManager* manager = new SensorManager(dataManager);

    printf("Setting up sensors\n");
    SoundSensor* soundSensor = new SoundSensor(A0, SOUND_SENSOR_DELAY);
    soundSensor->SetName(std::string("Sound"));

    LightSensor* lightSensor = new LightSensor(A1, LIGHT_SENSOR_DELAY);
    lightSensor->SetName(std::string("Light"));

    DHTSensor* dhtSensor = new DHTSensor(D4, DHT_SENSOR_DELAY);
    dhtSensor->SetName(std::string("DHT"));

    manager->AddSensor(soundSensor);
    manager->AddSensor(lightSensor);
    manager->AddSensor(dhtSensor);

    printf("Setting location\n");
    Location* location = new Location(DEVICE_ID);
    location->SetBuilding("MU8");
    location->SetRoom("R22");
    button.rise(callback(&display, &Display::ScreenChangerCallback));

    printf("Running manager\n");
    manager->Run();
    
    display.SetManager(manager);
    display.SetLocation(location);
}
