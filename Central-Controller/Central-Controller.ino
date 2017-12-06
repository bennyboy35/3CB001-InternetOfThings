#include <Tone.h>

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
int Available = 0;
int LeftBrake = 0;
int RightBrake = 0;
int Timeout = 0;
int PoweredDownLeft = 0;
int PoweredDownRight = 0;

void setup() {
 u8g2.begin();
 Serial.begin(9600);
 Serial1.begin(9600);
 u8g2.clearBuffer();
 u8g2.setFont(u8g2_font_ncenB08_tr);

    u8g2.drawStr(5,35,"Initializing");
    u8g2.sendBuffer();
  while(Available == 0){
    if (Serial.available() && Serial1.available()) {
    Available = 1;
  }
  Timeout = Timeout + 1;
  Serial.println(Timeout);
  if(Timeout == 5000){
    u8g2.clearBuffer();
    u8g2.drawStr(5,35,"Retrying Connection");
    u8g2.sendBuffer();
    }
  
  }

}

void loop() {

   if (Serial.available() && Serial1.available()) {
    UpdateScreen();
    if(Serial.read() == 0){
    SetScreen(0);
    }
    
    if(Serial.read() == 1){
    SetScreen(1);
    }

    
    if(Serial.read() == 5){
      SetScreen(5);
    }

    if(Serial1.read() == 2){
    SetScreen(2);
    }

    if(Serial1.read() == 3){
    SetScreen(3);
    }
    
    if(Serial1.read() == 6){
    SetScreen(6);
    }
    Serial.flush();
    Serial1.flush();
   }
}

void SetScreen(int Bulb){
  if(Bulb == 0){
    LeftBrake = 1;
    PoweredDownLeft = 0;
  }
  if(Bulb == 1){
    LeftBrake = 0;
    PoweredDownLeft = 0;
  }
  if(Bulb == 5){
    PoweredDownLeft = 1;
    
  }


  if(Bulb == 2){
    RightBrake = 1;
    PoweredDownRight = 0;
  }
  if(Bulb == 3){
    RightBrake = 0;
    PoweredDownRight = 0;
  }
  if(Bulb == 6){
    PoweredDownRight = 1;
    
  }
}

void UpdateScreen(){
  u8g2.clearBuffer();
  if(LeftBrake == 1){
    u8g2.drawStr(5,15,"L Brake Bulb Failed");
  }
  if(RightBrake == 1){
    u8g2.drawStr(5,55,"R Brake Bulb Failed");
  }

  if(PoweredDownLeft == 1 && PoweredDownRight == 1){
    u8g2.clearBuffer();
    u8g2.drawStr(5,35,"Powered Down");
  }
  
  if(LeftBrake == 0 && RightBrake == 0 && PoweredDownLeft == 0 && PoweredDownRight == 0){
    u8g2.drawStr(5,35,"All Bulbs Operational");
  }
  u8g2.sendBuffer();
}

