/*
Aşağıdaki kütüphaneleri indirin
https://codeload.github.com/mroger/TEA5767/zip/refs/heads/master
https://github.com/olikraus/U8g2_Arduino
*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

#include <TEA5767N.h>
TEA5767N radio = TEA5767N();


//float frequency = 87.0f;
float frequency = 104.0f;
float previousFrequency = 0;
int signalStrength = 0;

char deger;



void printFrequency(float frequency2)
{
  String frequencyString = String(frequency2,1);
  u8g2.print(frequencyString);
}

void printSignalStrength()
{
  signalStrength = radio.getSignalLevel();
  String signalStrenthString = String(signalStrength);
  if(signalStrength >=15)
  {
    u8g2.print("seviye5");
  }else if(signalStrength >=11 && signalStrength <15)
  {
    u8g2.print("seviye4");
  }
  else if(signalStrength >=9 && signalStrength <11)
  {
    u8g2.print("seviye3");
  }
   else if(signalStrength >=7 && signalStrength <9)
  {
    u8g2.print("seviye2");
  }
   else if(signalStrength <7)
  {
    u8g2.print("seviye1");
  }
}

void printStereo()
{
    boolean isStereo = radio.isStereo();
     if(isStereo)
    {
      u8g2.print("Stereo");
    }
}

void oledYaz(){
  u8g2.clearBuffer();
  u8g2.setCursor(34, 20);
  printFrequency(frequency);
  u8g2.setCursor(40, 40);
  printSignalStrength();
  u8g2.setCursor(66, 10);
  printStereo();
  u8g2.sendBuffer();
}

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();   // enable UTF8 support for the Arduino print() function
  u8g2.setFont(u8g2_font_t0_22b_te);  
  u8g2.setFontDirection(0);
  
  /*u8g2.clearBuffer();
  u8g2.setCursor(8, 20);
  u8g2.print("r");
  u8g2.sendBuffer();*/
  
   radio.setMonoReception();
   radio.setStereoNoiseCancellingOn();
   radio.selectFrequency(frequency);
   Serial.begin(9600);
   oledYaz();
}

void loop() {
  if(Serial.available()){
    deger=Serial.read();
    if(deger=='u'){
      if(frequency<107.0f){
      frequency+=0.1f;
      radio.selectFrequency(frequency);
      oledYaz();
      }
    }
    if(deger=='d'){
      if(frequency>87.0f){
    frequency-=0.1f;
    radio.selectFrequency(frequency);
    oledYaz();
    }
  }
  }
  
}
