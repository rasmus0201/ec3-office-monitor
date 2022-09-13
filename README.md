# Prerequisites
For this you will need the following software/hardware:

### Hardware:
- 1 &times; STM32 F7 Discovery board (DISCO-F746NG)
- 1 &times; Base shield
- 1 &times; USB cabel (USB to micro B)
- 1 &times; Grove Button v1.2
- 1 &times; Grove Buzzer v1.2
- 1 &times; Grove Light Sensor v1.2
- 1 &times; Grove Sound Sensor v1.6
- 1 &times; Grove Temperature&Humidity Sensor Pro (DHT22) v1.3
- 5 &times; 26AWG Grove Cable
- 1 &times; Ethernet cable

### Software:
- Mbed Studio (or the online compiler, or the CLI version)

# Installation
1. Clone this repository: `https://github.com/rasmus0201/ec3-office-monitor.git`
2. Make sure dependencies (libraries) are installed
   - mbed-os (version 6.16.0 - commit `54e8693ef4ff7e025018094f290a1d5cf380941f`) (import from `https://github.com/ARMmbed/mbed-os.git`)
   - BSP_DISCO_F746NG (version commit `85dbcff443aa20e932494823e42c6d2a9550d17a`) (import from `https://os.mbed.com/teams/ST/code/BSP_DISCO_F746NG/`)
   - mbed-dht (version commit `db94a44739cda011675bf3756cc35980f9c4d3be`) (import from `https://github.com/rasmus0201/mbed-dht.git`)
   - mbed-http-client (version commit `72a23a5fb311d2c8c12eea9e12a075a0a0e7220c`) (import from `https://github.com/rasmus0201/mbed-http-client.git`)
   - mbed-rtc (version commit `efdb021294f264d95d7c8b071119c55e05938cc6`) (import from `https://github.com/rasmus0201/mbed-rtc.git`) this will also download `ntp-client` which is working on version `e919cfb14e2029efafc0d1288a0223cbd09811f0`
3. If running own server, change API_BASE_URL in `defs.h`.
4. Compile the code on your favorite platform
5. Upload the binary to the board

# Serial connection
Note that this project does not use the normal baud rate, it uses `115200`!

# Documentation
Find the docs in [Documentation.md](Documentation.md)
