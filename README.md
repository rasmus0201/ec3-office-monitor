* √ Serie nummber / id nummer til API

* Lokation - Indtastning via Serial/Touch hvilket:
    - Bygning
    - Lokale

* RTC:
    - √ Opsæt Real-Time Clock for at få timestamps på sensore

* UI:
    - √ Boot skærm
    - √ Menu/hjemme skærm
    - √ Lokations-skærm (TODO API?)
    - Info-skærm
        - Lyssensor
        - Lydsensor
        - Vibrationssensor
        - Temperatur
        - Luftfugtighed

        - Light / dark mode
        - Dag / nat (tid)

* Components:
    - Keyboard
    - LcdButton
        - Display an interactive button
    - √ SensorManager
        - √ Starts all Sensors
    - √ SensorInInterface
        - √ ButtonSensor
        - √ TouchSensor
        - √ VibrationSensor
        - √ LightSensor
        - √ TemperatureSensor
        - √ HumiditySensor
        - √ SoundSensor
        
        - √ Start on new thread
        - √ Needs to take in AnalogIn / DigitalIn
    - √ SensorOutInterface
        - √ LedSensor
        - √ BuzzerSensor
        - √ Start on new thread


TODO:

- √ Make timestamps work
- √ Push data to API
    - √ Alter RTC library to take in the Network connection so it can be reused
- √ Boot skærm
- Screens
    - √ home
    - √ location
    - data/info/sensors
- Logic
    - Moving average datapoints
    - If sound > threshold = turn on led / display on screen
    - If vibration > threshold = turn on led / display on screen
    - If temp > threshold = turn on led / display on screen - "start a/c" -> turn servo motor
    - If humid > threshold = turn on led / display on screen - "start a/c" -> turn servo motor
- Documentation
- Optimize
    - Memory usage
    - √ Socket reuse
    - API use of precision timestamps
    - Keyboard on screen to choose location

