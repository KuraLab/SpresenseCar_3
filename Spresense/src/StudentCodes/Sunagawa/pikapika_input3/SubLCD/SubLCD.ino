
#if (SUBCORE != 1)
#error "Core selection is wrong!!"
#endif
#include <MP.h>

// LCD周りの設定
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Fonts/FreeSansOblique24pt7b.h"
/* CS はハードウェア制御のため設定しなくてもよい*/
#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 tft= Adafruit_ILI9341(&SPI,TFT_DC, TFT_CS, TFT_RST);

// LCDライブラリ周りの設定
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define PINK 0xF81F
#define ORANGE 0xFBE0

double pr;

 

void setup() {
  // put your setup code here, to run once:
  MP.begin();
  tft.begin(40000000);
  //tft.begin();
  tft.setRotation(3); // 画面回転
  tft.setFont(&FreeSansOblique24pt7b);
  //attachTimerInterrupt(&flip, 5000000);

  
  
  
}

void loop() {
  int      ret;
  int8_t   msgid;
  double *packet;
  // put your main code here, to run repeatedly:
  //int ret = MP.Recv(msgid,msg_ptr,0);
   ret = MP.Recv(&msgid, &packet);
   pr=*packet;
  //scr=*msg_ptr;
  //Serial.println(scr);
    flip();
    //delay(1000);
    //MPLog("%lf",est_packet_ptr->estimation);
}

void flip(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  //tft.setCursor(10,40);
  //tft.setTextSize(1);
  //tft.println("Estimation:");
  tft.setCursor(70,120);
  tft.setTextSize(1);
  tft.printf("%4.2f",pr);
}
