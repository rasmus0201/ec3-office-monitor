#include <string>
#include <vector>
#include <ctime>
#include <cctype>
#include <algorithm>
#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "helpers.h"
#include "Display.h"
#include "Location.h"
#include "Collection.h"
#include "CollectionElement.h"
#include "SensorManager.h"
#include "SensorInterface.h"

using namespace Bundsgaard;

Display::Display()
{
    this->SetStartVariables();
}

void Display::SetManager(SensorManager* manager)
{
    this->manager = manager;
}

void Display::SetLocation(Location* location)
{
    this->location = location;
}

void Display::Setup()
{
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    HAL_Delay(500);

    uint8_t status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    if (status != TS_OK) {
        BSP_LCD_Clear(LCD_COLOR_RED);
        BSP_LCD_SetBackColor(LCD_COLOR_RED);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN INIT FAIL", CENTER_MODE);
    }

    HAL_Delay(500);
}

void Display::Loop()
{
    this->SetLoopVariables();
    this->Clear();
    this->FontMedium();

    this->thread.start(callback(this, &Display::Worker));
}

void Display::Worker()
{
    TS_StateTypeDef TS_State;

    while(true) {
        BSP_TS_GetState(&TS_State);

        if (this->currentState == this->prevState && this->currentState == DisplayScreen::DATA) {
            this->ShowData();
        }

        if (this->currentState != this->prevState) {
            this->Clear();

            switch(this->currentState) {
                case DisplayScreen::NO_STATE:
                    this->ShowHome();
                    break;
                case DisplayScreen::HOME:
                    this->ShowHome();
                    break;
                case DisplayScreen::LOCATION:
                    this->ShowLocation();
                    break;
                case DisplayScreen::DATA:
                    this->ShowData();
                    break;
            }

            this->prevState = this->currentState;
        }

        HAL_Delay(50);
    }
}

void Display::ShowHome()
{
    this->Clear();
    this->FontBig();
    this->TextCentered("Welcome to office monitor");
    this->FontMedium();
    this->TextCentered("Press button to switch screen", LINE(2));
}

void Display::ShowLocation()
{
    this->Clear();
    this->FontBig();
    this->TextCentered("Enhed: " + this->location->GetDeviceName());
    this->TextCentered("Lokale: " + this->location->GetLocationName() + " (#" + std::to_string(this->location->GetLocationId()) + ")" , LINE(2));
}

void Display::ShowData()
{
    for (int i = 1; i < 10; i++) {
        BSP_LCD_ClearStringLine(LINE(i));
    }

    this->FontMedium();
    this->TextSpaceBetween(
        "Location:",
        this->location->GetLocationName() + " #" + std::to_string(this->location->GetLocationId()),
        LINE(0)
    );

    time_t currentTime = time(NULL);
    struct tm* localeTime;
    localeTime = localtime(&currentTime);

    {
        std::string dateTime = to_weekdayname(localeTime->tm_wday) + ". ";
        dateTime += std::to_string(localeTime->tm_mday) + ". ";
        dateTime += to_monthname(localeTime->tm_mon) + ".";

        this->TextSpaceBetween("Date:", dateTime, LINE(1));
    }

    {
        std::string strTime = pad_left(std::to_string(localeTime->tm_hour), 2) + ":";
        strTime += pad_left(std::to_string(localeTime->tm_min), 2, '0') + ":";
        strTime += pad_left(std::to_string(localeTime->tm_sec), 2, '0');

        this->TextSpaceBetween("Time:", strTime, LINE(2));
    }


    Collection* collection = manager->GetDataCollection();
    vector<std::string> keys = manager->GetSensorKeys();

    uint8_t SCREEN_WIDTH_CHARS = 34;
    uint8_t precisionVal = 2;
    uint8_t lineNo = 3;
    for (auto &sensor : keys) {
        float avg = collection->Average(sensor);
        std::string name = sensor;
        name[0] = std::toupper(name[0]);
        std::string averagePrecision = std::to_string(avg).substr(0, std::to_string(avg).find(".") + precisionVal + 1);

        this->TextSpaceBetween(
            pad_right(name + ":", SCREEN_WIDTH_CHARS / 2),
            pad_left(averagePrecision, SCREEN_WIDTH_CHARS / 2),
            LINE(lineNo)
        );

        lineNo++;
    }
}

void Display::SetStartVariables()
{
    this->background = LCD_COLOR_WHITE;
    this->color = LCD_COLOR_BLUE;
}

void Display::SetLoopVariables()
{
    this->background = LCD_COLOR_BLACK;
    this->color = LCD_COLOR_WHITE;
}

void Display::Clear()
{
    BSP_LCD_Clear(this->background);
    BSP_LCD_SetBackColor(this->background);
    BSP_LCD_SetTextColor(this->color);
    this->FontMedium();
}

void Display::FontSmall()
{
    BSP_LCD_SetFont(&Font12);
}

void Display::FontMedium()
{
    BSP_LCD_SetFont(&Font20);
}

void Display::FontBig()
{
    BSP_LCD_SetFont(&Font24);
}

void Display::Delay(uint32_t delay)
{
    HAL_Delay(delay);
}

void Display::TextCentered(std::string text, uint16_t yOffset)
{
    uint16_t fontHeight = ((sFONT *)BSP_LCD_GetFont())->Height;
    uint32_t screenHeight = BSP_LCD_GetYSize();

    BSP_LCD_DisplayStringAt(0, int((screenHeight / 2) - (fontHeight / 2)) + yOffset, (uint8_t *)text.c_str(), CENTER_MODE);
}

void Display::TextLeft(std::string text, uint16_t yOffset)
{
    BSP_LCD_DisplayStringAt(0, yOffset, (uint8_t *)text.c_str(), LEFT_MODE);
}

void Display::TextRight(std::string text, uint16_t yOffset)
{
    BSP_LCD_DisplayStringAt(0, yOffset, (uint8_t *)text.c_str(), RIGHT_MODE);
}

void Display::TextSpaceBetween(std::string textLeft, std::string textRight, uint16_t yOffset)
{
    this->TextLeft(textLeft, yOffset);
    this->TextRight(textRight, yOffset);
}

void Display::ScreenChangerCallback()
{
    // Algorithm:
    // By using modulus the screen state will circulate states like:
    // -1 -> 0
    // 0 -> 1
    // 1 -> 2
    // 2 -> 0
    // 0 -> 1, etc...
    this->currentState = static_cast<DisplayScreen>((this->currentState + 1) % 3);
}
