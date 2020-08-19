#include <string>
#include <vector>
#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "Display.h"
#include "Location.h"
#include "SensorManager.h"
#include "SensorInterface.h"

using namespace Bundsgaard;

Display::Display(SensorManager* manager, Location* location)
{
    this->manager = manager;
    this->location = location;
    this->SetStartVariables();
}

void Display::Setup()
{
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    HAL_Delay(1000);

    uint8_t status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    if (status != TS_OK) {
        BSP_LCD_Clear(LCD_COLOR_RED);
        BSP_LCD_SetBackColor(LCD_COLOR_RED);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN INIT FAIL", CENTER_MODE);
    }

    HAL_Delay(1000);
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

        if (this->currentState != this->prevState) {
            printf("Current: %d, prev = %d\n", this->currentState, this->prevState);  
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

        HAL_Delay(100);
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
    this->TextCentered("Bygning: " + this->location->GetBuilding());
    this->TextCentered("Lokale: " + this->location->GetRoom(), LINE(2));
}

void Display::ShowData()
{
    this->Clear();

    // std::vector<SensorInterface *> sensors = *manager->GetSensorsIn();
    // for (auto &sensor : sensors) {
    //     printf("Sensor: %s | ", sensor->GetName().c_str());
    //     printf("Value: %4.2f\n\n", sensor->GetDataManager()->dataStore->Average());
    // }
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