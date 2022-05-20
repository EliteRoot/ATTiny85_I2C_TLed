#define F_CPU 8000000  // This is used by delay.h library

#include <stdlib.h>

#include <avr/io.h>        // Adds useful constants
#include <util/delay.h>    // Adds delay_ms and delay_us functions
 
#include <avr/sleep.h>
#include <avr/interrupt.h>

// Routines to set and claer bits (used in the sleep code)
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


#include <Wire.h>
#include <TinyBME280.h>
#include <Tiny4kOLED.h>

int const sda = 0;
int const scl = 2;

const int Degree = 138;
const int Tiny = 128;

int calibrationFactor = 0; 
volatile boolean f_wdt = 1;

void setup() {
    // Set up FAST PWM 
  TCCR0A = 2<<COM0A0 | 2<<COM0B0 | 3<<WGM00;  // Set control register A for Timer 0
  TCCR0B = 0<<WGM02 | 1<<CS00;                // Set control register B for Timer 0
  TCCR1 = 0<<PWM1A | 0<<COM1A0 | 1<<CS10;     // Set control register for Timer 1
  GTCCR = 1<<PWM1B | 2<<COM1B0;               // General control register for Timer 1

  
  pinMode(1, INPUT);   pinMode(3, INPUT);  pinMode(4, INPUT);   pinMode(5, INPUT);   //power saving technique 
  digitalWrite(1, LOW); digitalWrite(3, LOW); digitalWrite(4, LOW); digitalWrite(5, LOW); //power saving technique 
     
  oled.begin();
  oled.clear();
  oled.on();
  oled.setFont(FONT6X8);
  oled.switchRenderFrame();
  Wire.begin();
  BME280setI2Caddress(0x76); //I2C Sensor Address
  oled.setCursor(32, 2);
  oled.print("Connect");
  oled.setCursor(32, 3);
  oled.print("0x76");
  BME280setup(); 

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
  setup_watchdog(9);
}

float BME280altitude (float referencePressure) {
  return ((float)-45846.2)*(pow(((float)BME280pressure()/(float)referencePressure), 0.190263) - (float)1);
}
  
void loop() {
    if (f_wdt==1) {  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
    f_wdt=0;       // reset flag
    BME280setup(); 
   
   BMEShowTemp();
   delay(3000);
   BMEShowPwr();
   delay(3000);
   BMEShowTemp();

   BME280sleep();
   system_sleep(); 
  }
}

void BMEShowTemp() {
  int cels = BME280temperature();
  delay(100);
  int humid = BME280humidity();
  delay(100);
  oled.clear();
  oled.setFont(FONT6X8);
  oled.setCursor(32, 2);
  oled.print(cels/100+2); oled.print("."); oled.print(cels / 10 % 10); oled.print(" "); oled.print("?C");
  oled.setCursor(32, 3);
  oled.print(humid/100); oled.print("."); oled.print(humid / 10 % 10); oled.print(" %RH");
  oled.switchFrame();
}

void BMEShowPwr() {
     //  int alti = BME280altitude(1013.25);    
  int battery = min(22528/analogRead(12),100);
  delay(100);
  oled.clear();
  oled.setFont(FONT6X8);
  oled.setCursor(32, 2);
  oled.print(BME280pressure()/100);
  delay(100);
  oled.print(" hPa"); 
  oled.setCursor(32, 3);
  oled.print("PWR ");  oled.print(battery);  oled.print("%"); 
  oled.switchFrame();
}

void system_sleep() {
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sleep_mode();                        // System actually sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out 
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
  
}

void setup_watchdog(int ii) {
  byte bb;
  int ww;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
  f_wdt=1;  // set global flag
}
