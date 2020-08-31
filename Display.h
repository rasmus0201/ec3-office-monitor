/**
 * @file Display.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Display header file
 * @version 0.1
 * @date 2020-08-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

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
    /**
     * @brief Enum to tell screen states apart 
     * 
     */
    enum DisplayScreen {
        NO_STATE = -1,
        HOME,
        LOCATION,
        DATA
    };
    
    /**
     * @brief Display class with different helper functions
     *        and functions for displaying different screen states
     * 
     */
    class Display
    {
        public:
            /**
             * @brief Construct a new Display object
             * 
             * @param manager 
             * @param location 
             */
            Display(SensorManager* manager, Location* location);

            /**
             * @brief Initialize the screen
             * 
             */
            void Setup();

            /**
             * @brief Clear the screen
             * 
             */
            void Clear();

            /**
             * @brief Set the starting variables
             * 
             */
            void SetStartVariables();

            /**
             * @brief Set the loop variables
             * 
             */
            void SetLoopVariables();

            /**
             * @brief Set the font to small
             * 
             */
            void FontSmall();

            /**
             * @brief Set the font to medium
             * 
             */
            void FontMedium();

            /**
             * @brief Set the font to big
             * 
             */
            void FontBig();

            /**
             * @brief Delay the screen (HAL_Delay)
             * 
             * @param delay 
             */
            void Delay(uint32_t delay);

            /**
             * @brief Display vertially and horizontally centered string.
             *        The y-position can be at an offset up or down.
             * 
             * @param text 
             * @param yOffset 
             */
            void TextCentered(std::string text, uint16_t yOffset = 0);

            /**
             * @brief Display left-aligned text
             * 
             * @param text 
             * @param yOffset 
             */
            void TextLeft(std::string text, uint16_t yOffset = 0);

            /**
             * @brief Display right-aligned text
             * 
             * @param text 
             * @param yOffset 
             */
            void TextRight(std::string text, uint16_t yOffset = 0);

            /**
             * @brief Display right-aligned text
             * 
             * @param textLeft
             * @param textRight
             * @param yOffset 
             */
            void TextSpaceBetween(std::string textLeft, std::string textRight, uint16_t yOffset = 0);

            /**
             * @brief Start the display loop. Will set variables and start thread.
             * 
             */
            void Loop();

            /**
             * @brief The method for the display thread
             * 
             */
            void Worker();

            /**
             * @brief Show the home screen
             * 
             */
            void ShowHome();

            /**
             * @brief Show the location screen
             * 
             */
            void ShowLocation();

            /**
             * @brief Show the data screen
             * 
             */
            void ShowData();

            /**
             * @brief Interrupt callback of the screen state changingn mechanism
             * 
             */
            void ScreenChangerCallback();

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
