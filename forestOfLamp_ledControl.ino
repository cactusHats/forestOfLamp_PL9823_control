#include "Lamp.h"
#include "define.h"

Lamp lamps[NUM_LAMP]; //インスタンス宣言

int identifier = 0;

void setup() {
  Serial.begin(115200);
  initializeLamps(); //ランプ初期化
  lamps[0].ledStart(); //NeoPixel Start
}

void loop() {
  //パケット受信
  //Serial.println(NUM_LED * int(Color::NUM_COLOR));
  if (Serial.available() > NUM_LED * int(Color::NUM_COLOR)) {
    identifier = Serial.read();
    if (identifier == 0xFF) {
      for (int i = 0; i < NUM_LAMP; i++) {
        int r = Serial.read();
        int g = Serial.read();
        int b = Serial.read();
        lamps[i].setRgbValue(r, g, b);
      }
      
      //バッファクリア
      while (Serial.available() > 0) {
        Serial.read();
      }
    }
  }

  //LEDに反映
  for (int i = 0; i < NUM_LAMP; i++) {
    lamps[i].updateColor();
    lamps[i].outputColor();
    //dmp(i); //シリアルモニタ出力
  }
  pixels.show();
}

void dmp(int id_) {
  Serial.print(lamps[id_].getId());
  Serial.print(" ");
  Serial.print(lamps[id_].getR());
  Serial.print(" ");
  Serial.print(lamps[id_].getG());
  Serial.print(" ");
  Serial.println(lamps[id_].getB());
}

void initializeLamps() {
  //ランプのIDを初期化
  for (int i = 0; i < NUM_LAMP; i++) {
    lamps[i].setId(i);
    lamps[i].setRgbValue(10, 0, 10);
  }
}
