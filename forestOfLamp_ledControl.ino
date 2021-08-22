#include "define.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

Adafruit_NeoPixel pixels(NUM_LAMP, PIN_LED, NEO_GRB + NEO_KHZ800);

int c_rgbVal[NUM_LAMP][int(Color::NUM_COLOR)]; //現在値
int d_rgbVal[NUM_LAMP][int(Color::NUM_COLOR)]; //目標値
int identifier = 0;
long u_timeNow = 0;
long u_timeThen = 0;
long o_timeNow = 0;
long o_timeThen = 0;

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.clear();

  Serial.begin(BAUDRATE);

  initializeLamps();
}

void loop() {

  //データ受信
  while (Serial.available() > int(Color::NUM_COLOR)) {
    identifier = Serial.read(); //先頭識別子(id)

    //管轄範囲のランプIDを受け取ったら
    if (LAMPRANGE_MIN + ID_BIAS <= identifier && identifier <= LAMPRANGE_MAX + ID_BIAS) {
      //データを読み込む
      d_rgbVal[identifier - ID_BIAS - LAMPRANGE_MIN][int(Color::Red)] = Serial.read();
      d_rgbVal[identifier - ID_BIAS - LAMPRANGE_MIN][int(Color::Green)] = Serial.read();
      d_rgbVal[identifier - ID_BIAS - LAMPRANGE_MIN][int(Color::Blue)] = Serial.read();

      //追加 21.01.25
      //c_rgbVal[identifier - ID_BIAS - LAMPRANGE_MIN][int(Color::Red)] = d_rgbVal[identifier - ID_BIAS - LAMPRANGE_MIN][int(Color::Red)] * 0.4;
      //c_rgbVal[identifier - ID_BIAS - LAMPRANGE_MIN][int(Color::Green)] = d_rgbVal[identifier - ID_BIAS - LAMPRANGE_MIN][int(Color::Green)] * 0.4;
      //c_rgbVal[identifier - ID_BIAS - LAMPRANGE_MIN][int(Color::Blue)] = d_rgbVal[identifier - ID_BIAS - LAMPRANGE_MIN][int(Color::Blue)] * 0.4;
      
    }

    /*
      //バッファクリア
      while (Serial.available() > 0) {
      Serial.read();
      }
    */
  }

  //現在時刻取得
  u_timeNow = millis();
  o_timeNow = millis();

  //値更新
  if (u_timeNow - u_timeThen > UPDATE_INTERVAL) {
    updateColor();
    checkColorRate();
    u_timeThen = millis();
  }

  //LED出力
  if (o_timeNow - o_timeThen > OUTPUT_INTERVAL) {
    outputColor();
    o_timeThen = millis();
  }
}

void updateColor() {
  for (int i = 0; i < NUM_LAMP; i++) {
    /*
      //1ステップで変化
      c_rgbVal[i][int(Color::Red)] = d_rgbVal[i][int(Color::Red)];
      c_rgbVal[i][int(Color::Green)] = d_rgbVal[i][int(Color::Green)];
      c_rgbVal[i][int(Color::Blue)] = d_rgbVal[i][int(Color::Blue)];
    */

    //ゆっくり変化
    if (c_rgbVal[i][int(Color::Red)] != d_rgbVal[i][int(Color::Red)]) {
      if (c_rgbVal[i][int(Color::Red)] < d_rgbVal[i][int(Color::Red)]) c_rgbVal[i][int(Color::Red)] += CHANGE_RATE;
      else c_rgbVal[i][int(Color::Red)] -= CHANGE_RATE;
    }
    if (c_rgbVal[i][int(Color::Green)] != d_rgbVal[i][int(Color::Green)]) {
      if (c_rgbVal[i][int(Color::Green)] < d_rgbVal[i][int(Color::Green)]) c_rgbVal[i][int(Color::Green)] += CHANGE_RATE;
      else c_rgbVal[i][int(Color::Green)] -= CHANGE_RATE;
    }
    if (c_rgbVal[i][int(Color::Blue)] != d_rgbVal[i][int(Color::Blue)]) {
      if (c_rgbVal[i][int(Color::Blue)] < d_rgbVal[i][int(Color::Blue)]) c_rgbVal[i][int(Color::Blue)] += CHANGE_RATE;
      else c_rgbVal[i][int(Color::Blue)] -= CHANGE_RATE;
    }
  }
}

void outputColor() {
  for (int i = 0; i < NUM_LAMP; i++) {
    pixels.setPixelColor(i, pixels.Color(c_rgbVal[i][int(Color::Green)], c_rgbVal[i][int(Color::Red)], c_rgbVal[i][int(Color::Blue)]));
  }
  pixels.show();
}

void checkColorRate() {
  for (int i = 0; i < NUM_LAMP; i++) {
    if (d_rgbVal[i][int(Color::Red)] > ABNORMAL_THRESHOLD || d_rgbVal[i][int(Color::Green)] > ABNORMAL_THRESHOLD || d_rgbVal[i][int(Color::Blue)] > ABNORMAL_THRESHOLD) {
      d_rgbVal[i][int(Color::Red)] = 0;
      d_rgbVal[i][int(Color::Green)] = 0;
      d_rgbVal[i][int(Color::Blue)] = 0;
    }
  }
}

void initializeLamps() {
  for (int i = 0; i < NUM_LAMP; i++) {
    d_rgbVal[i][int(Color::Red)] = 30;
    d_rgbVal[i][int(Color::Green)] = 30;
    d_rgbVal[i][int(Color::Blue)] = 30;
  }
}
