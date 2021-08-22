#include "Lamp.h"
#include "ledSetup.h"

//コンストラクタ
Lamp::Lamp() {
  //目標値
  d_r = 0;
  d_g = 0;
  d_b = 0;

  //現在値
  c_r = 0;
  c_g = 0;
  c_b = 0;

  //id
  id = 0;
}

void Lamp::setRgbValue(int r_, int g_, int b_) {
  //目標値に値をセット
  d_r = r_;
  d_g = g_;
  d_b = b_;
}

void Lamp::setId(int id_) {
  //IDに値をセット
  id = id_;
}

void Lamp::updateColor() {
  /*
    //1ステップで変化
    c_r = d_r;
    c_g = d_g;
    c_b = d_b;
  */

  //ゆっくり変化
  if (c_r != d_r) {
    if (c_r < d_r) c_r += changeRate;
    else c_r -= changeRate;
  }
  if (c_g != d_g) {
    if (c_g < d_g) c_g += changeRate;
    else c_g -= changeRate;
  }
  if (c_b != d_b) {
    if (c_b < d_b) c_b += changeRate;
    else c_b -= changeRate;
  }
}

void Lamp::outputColor() {
  pixels.setPixelColor(id, pixels.Color(c_g, c_r, c_b));
  //pixels.show();
}


int Lamp::getR() {
  return c_r;
}

int Lamp::getG() {
  return c_g;
}

int Lamp::getB() {
  return c_b;
}

int Lamp::getId() {
  return id;
}

void Lamp::ledStart() {
  pixels.begin();
  pixels.clear();
}
