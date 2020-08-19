#ifndef BUNDSGAARD_DISPLAY_H
#define BUNDSGAARD_DISPLAY_H

#include <string>
#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "Location.h"
#include "SensorManager.h"

namespace Bundsgaard
{
    enum DisplayScreen {
        NO_STATE = -1,
        HOME,
        LOCATION,
        DATA
    };
    
    class Display
    {
        public:
            Display(SensorManager* manager, Location* location);
            void Setup();
            void Clear();
            void SetStartVariables();
            void SetLoopVariables();
            void FontSmall();
            void FontMedium();
            void FontBig();
            void Delay(uint32_t delay);
            void TextCentered(std::string text, uint16_t yOffset = 0);

            void Loop();
            void Worker();

            void ShowHome();
            void ShowLocation();
            void ShowData();

        public:
            enum DisplayScreen currentState = HOME;
            enum DisplayScreen prevState = NO_STATE;
        
        private:
            uint32_t background;
            uint32_t color;

            SensorManager* manager;
            Location* location;
            Thread thread;
    };
}

#endif
