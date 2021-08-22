#pragma once

class Lamp {
    //目標値
    int d_r;
    int d_g;
    int d_b;

    //現在値
    int c_r;
    int c_g;
    int c_b;

    //id
    int id;

    //変化の速さ
    const int changeRate = 1;

  public:
    //デフォルトコンストラクタ
    Lamp();
    //コンストラクタ
    Lamp(int id_) : id(id_) {};

    void setRgbValue(int r_, int g_, int b_);
    void setId(int id_);
    void updateColor();
    void outputColor();
    
    int getR();
    int getG();
    int getB();
    int getId();

    void ledStart();
};
