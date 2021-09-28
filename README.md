# speeduino-ardugauge

 An OLED gauge for the Speeduino ECU. Uses UART (secondary serial) for communication. See [demo video](https://youtu.be/CHvzBlRpPmE).
 
 **NOTE:** The gauge shares the same Serial port for communcations with Speeduino ECU and USB connection for programming. Disconnect from the ECU if you wish to upload the Arduino sketch.
 
## Parts List
1. **Arduino Nano** - should work with most 328P arduino boards
3. **Monochrome OLED display** - 128x64 px, SSD1306 driver, I2C interface
4. **Push button** - with optional pull-up resistor.
5. **Connector** of your choice.

## Basic Pinout
|Arduino Pin| Connects To |
|-----------|-------------|
|5V         |Speeduino 5V |
|0-RX       |Speeduino TX3|
|1-TX       |Speeduino RX3|
|GND        |Speeduino GND|
|5V         |OLED 5V      |
|A5         |OLED SCL     |
|A4         |OLED SDA     |
|GND        |OLED GND     |
|D2         |Push Button  |
|GND        |Push Button  |

## Speeduino Settings
Enable `Secondary Serial` only. [Speeduino Manual](https://wiki.speeduino.com/en/Secondary_Serial_IO_interface)
