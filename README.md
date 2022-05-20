# ATTiny85_I2C_TLed
Building a Supercapacitor Circuit with a SHT15/BME, ATTiny85 and Micro OLED

I've been pulling from tons of repositories and rewriting stiched code for this frankencode project. Most of these chips are $2 knockoffs from Aliexpress that don't work like the rest of the bunch. So there's custom patches to registers all over.. like an SSD1306 128x64 bit driver running a 64x32 OLED display and writing start of display at 32, 32 , 0. It's madness! So enjoy the ride.. you've been warned. 



Programmer: USBtinyISP https://www.amazon.ca/gp/product/B07PBVXQP8/
Chip: ATTiny85 https://www.amazon.ca/gp/product/B09KCG3KFN/
BMP280 Digital 5V Temperature Humidity Sensor : https://www.amazon.ca/gp/product/B095JPCL4Q/
4-pin OLED Display Module 64x32 SSD1306 LCD Screen IIC Interface Module Super Bright Module For AVR STM32
: https://www.aliexpress.com/item/1005003852500419.html?spm=a2g0o.order_list.0.0.11041802JJ6Ero


Board Library: ATTinyCore ATTiny 25/35/45 (no bootloader)

TinyWireM Library by Adafruit 1.1.1 I2C Library for Trinket and Gemma..

Boards Managers:
https://dl.espressif.com/dl/package_esp32_index.json,http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json,http://drazzy.com/package_drazzy.com_index.json

Adafruit SSD1306 https://adafruit.github.io/Adafruit_SSD1306/html/class_adafruit___s_s_d1306.html

SSD1306xLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x64 displays 
: https://bitbucket.org/tinusaur/ssd1306xled

ssd1306xled, re-written and extended by Stephen Denne
: https://bitbucket.org/tinusaur/ssd1306xled

*Danigy/tiny-bme280 library
:https://github.com/Danigy/tiny-bme280/

*Tiny4kOLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x32 displays
Based on ssd1306xled, re-written and extended by Stephen Denne
: https://github.com/datacute/Tiny4kOLED

ATTiny Weather Station v3
: http://www.plasticki.com/list?2F9I

I2C - Inter-Integrated Circuit communications
: https://learn.adafruit.com/assets/44476

adafruit/Adafruit_SSD1306 
: https://github.com/adafruit/Adafruit_SSD1306

Tiny TFT Graphics Library v2
: http://www.technoblogy.com/list?2LJ2

ATTiny86  SleepMode
: https://www.re-innovation.co.uk/docs/sleep-modes-on-attiny85/

ASCII Tables
: https://www.techonthenet.com/ascii/chart.php 

BME280 Sleep Library
: https://github.com/G6EJD/BME280-Sleep-and-Address-change/blob/master/BME280_Sleep.ino

...and some cool super capacitors and solar panels from Digikey.
