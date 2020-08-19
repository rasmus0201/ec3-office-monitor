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

SensorManager* manager;
Location* location = new Location(DEVICE_ID);
Display display(manager, location);

void setup();
void setupDisplay();
void setupTouch();
void loop();

void btnMenuChangerCallback();

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

    display.Clear();
    display.TextCentered("Setting RTC...");
    Rtc* rtc = new Rtc(NTP_SYNC_INTERVAL);
    rtc->Start();

    display.Clear();
    display.TextCentered("Initializing sensors...");
    SensorManager* manager = new SensorManager(new DataManager(rtc));

    SoundSensor soundSensor(A0, SOUND_SENSOR_DELAY);
    soundSensor.SetName("Sound");

    LightSensor lightSensor(A1, LIGHT_SENSOR_DELAY);
    lightSensor.SetName("Light");

    DHTSensor dhtSensor(D4, DHT_SENSOR_DELAY);
    dhtSensor.SetName("DHT");

    manager->AddSensorIn(&soundSensor);
    manager->AddSensorIn(&lightSensor);
    manager->AddSensorIn(&dhtSensor);
    manager->Run();

    location->SetBuilding("MU8");
    location->SetRoom("R22");
    button.rise(&btnMenuChangerCallback);
}

void btnMenuChangerCallback()
{
    // -1 -> 0, 0 -> 1, 1 -> 2, 2 -> 0
    display.currentState = static_cast<DisplayScreen>((display.currentState + 1) % 3);
}