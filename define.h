enum class Color {
  Red,
  Green,
  Blue,
  NUM_COLOR
};

//ボーレート
#define BAUDRATE 250000

//ランプ設定
#define PIN_LED 6
#define NUM_LAMP 14
#define ID_BIAS 150 //IDバイアス
#define ABNORMAL_THRESHOLD 100 //これ以上の目標値を検知したら0にする（通信エラー対策）

//管轄ランプIDの設定
#define LAMPRANGE_MIN 70
#define LAMPRANGE_MAX 83

//LED制御設定
#define OUTPUT_INTERVAL 20 //LED出力の間隔
#define UPDATE_INTERVAL 20 //更新の間隔
#define CHANGE_RATE 1 //変化の速さ
#define GET_PACKET_NUM 4 //読み込みを開始するパケット数
