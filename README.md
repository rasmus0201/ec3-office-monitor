# Prerequisites
For this you will need the following software/hardware:

### Hardware:
- 1 &times; STM32 F7 Discovery board (DISCO-F746NG)
- 1 &times; Base shield
- 1 &times; USB cabel (USB to micro B)
- 1 &times; Grove Button v1.2
- 1 &times; Grove Buzzer v1.1b
- 1 &times; Grove LED Socket Kit v1.3
- 1 &times; Grove Red LED
- 1 &times; Grove Light Sensor v1.2 
- 1 &times; Grove Sound Sensor v1.3 
- 1 &times; Grove Temperature&Humidity Sensor Pro (DHT22) v1.3
- 6 &times; 26AWG Grove Cable
- 1 &times; Ethernet cable

### Software:
- Mbed Studio (or the online compiler, or the CLI version)

# Installation
1. Clone this repository: `https://github.com/rasmus0201/ec2-office-monitor.git`
2. Make sure dependencies (libraries) are installed
   - mbed-os (version 6.2.1 - commit `890f0562dc2efb7cf76a5f010b535c2b94bce849`) (import from `https://github.com/ARMmbed/mbed-os.git`)
   - BSP_DISCO_F746NG (version commit `85dbcff443aa20e932494823e42c6d2a9550d17a`) (import from `https://os.mbed.com/teams/ST/code/BSP_DISCO_F746NG/`)
   - mbed-dht (version commit `db94a44739cda011675bf3756cc35980f9c4d3be`) (import from `https://github.com/rasmus0201/mbed-dht.git`)
   - mbed-http-client (version commit `72a23a5fb311d2c8c12eea9e12a075a0a0e7220c`) (import from `https://github.com/rasmus0201/mbed-http-client.git`)
   - mbed-rtc (version commit `fba4e78f90cf4dc85ae4ec75f8d7eae3ef70f895`) (import from `https://github.com/rasmus0201/mbed-rtc.git`) this will also download `ntp-client` which is working on version `a4ccf62992b9adc5086a9afea08fa4deb2e2fbd7` 
3. Compile the code on your favorite platform
4. Upload the binary to the board

# Serial connection
Note that this project does not use the normal baud rate, it uses `115200`!

# Documentation
Find the docs in [Documentation.md](Documentation.md)
