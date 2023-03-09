// ピンアサイン
#define LED_LEADER 0  // リーダー確認用LED　わかりやすくするため
#define LED_OUTPUT 3  // 出力LED　位相を作る赤LED


#define LED_DETECT_0 LED0  // Spresence上検出状態lED
#define LED_DETECT_1 LED1  // presence上検出状態lED
#define LED_DETECT_2 LED2  // presence上検出状態lED
#define LED_DETECT_3 LED3  // presence上検出状態lED

#define SENSOR_IN_1 1  // 光センサ入力端子
#define SENSOR_IN_2 2  // 光センサ入力端子
// #include "LightSensor.h"
#define MY_MSGID 10  // ユーザ側で0を含む正値の Message ID (8 bit 符号付きデータ)を定義可。負値は不可。
#define INTERVAL 20  //attachInterrputとloopで単位が違うことに注意

#ifdef SUBCORE
#error "Core selection is wrong!!"
#endif
#include <MP.h>

int photoresistorPIN = A1;  //センサ入力読み取りピン
float lightValue = 0;       //センサ入力値

//ボタン番号
int button1 = 4;
int button2 = 5;
int button3 = 6;

//状態変数
int state = 0;

// DETECT回避用　
int kenti1 = 0;
int kenti2 = 0;

//ボタンONOFFチェック
int val1 = 0;
int valold1 = 0;
int val2 = 0;
int valold2 = 0;
int val3 = 0;
int valold3 = 0;

//受光部が光を検知したかのフラグ
int detectflag1 = 0;
int detectflag2 = 0;

//リーダーかどうかのデバック用フラグ
int L = 0;

//液晶＆シリアルモニタ用カウント
int count = 0;

//

//角速度比較時の閾値
double R = 0.1;  //

//プログラム全体の時間
double t = 0.0;  //

//detect時の時間を記録する文字
double timesave1 = 0.0;  //
double timesave2 = 0.0;  //

double phi = 0.0;   // 相互作用位相 [rad]
double phiO = 0.0;  // 相互作用位相 [rad]
double phip = 0.0;  // 相互作用位相 [rad]


double omega = 3.0;   //　初期の角速度
double Domega = 0.0;  //　上昇角速度
double Eomega = 0.0;  //　推定した相手の角速度

double phidot = 3.0;  //

double dt = 0.02;  // ステップ幅(要修正)

//ゲインパラメタ
double kappaB = 0.05;  //  最大値推定用

double lighttime0 = 0.0;  //
double lighttime1 = 0.0;  //
double lighttime2 = 0.0;  //

const unsigned int LED_DURATION = 10;  // LED点灯時間[回-dt]

double msg;

#define PI 3.14


// 受光処理
void DETECT_1(void) {
  if (state == 1) {
    detectflag1 = 1;   // 一台検知
    lighttime1 = 5.0;  // 点滅のための処理
  }
  // 最大値推定処理
  else if (state == 2) {
    if (timesave1 > 0) {
      Eomega = 50 * 2 * PI / (t - timesave1);  // 相手の角速度を推定
      kenti1 = kenti1 + 1;
      if ((Eomega - omega - Domega) > R && kenti1 > 2) {  // 相手のほうが大きかったら角速度上昇
        Domega = Domega + kappaB * (Eomega - omega - Domega);
        kenti1 = 0;
      }
    }
    timesave1 = t;
  }
}

// 受光処理　以下DETECT_1と同じ
void DETECT_2(void) {
  if (state == 1) {
    detectflag2 = 1;
    lighttime1 = 5.0;
  }

  else if (state == 2) {
    if (timesave2 > 0) {
      Eomega = 50 * 2 * PI / (t - timesave2);
      kenti2 = kenti2 + 1;

      if ((Eomega - omega - Domega) > R && kenti2 > 2) {
        Domega = Domega + kappaB * (Eomega - omega - Domega);
        kenti2 = 0;
      }
    }

    timesave2 = t;
  }
}


void setup() {
  pinMode(LED_LEADER, OUTPUT);      //PINを出力用に設定
  pinMode(LED_OUTPUT, OUTPUT);      //PINを出力用に設定
  pinMode(LED_DETECT_1, OUTPUT);    //PINを出力用に設定
  pinMode(LED_DETECT_2, OUTPUT);    //PINを出力用に設定
  pinMode(LED_DETECT_3, OUTPUT);    //PINを出力用に設定
  pinMode(LED_DETECT_0, OUTPUT);    //PINを出力用に設定
  pinMode(button1, INPUT);          //PINを入力用に設定
  pinMode(button2, INPUT);          //PINを入力用に設定
  pinMode(button3, INPUT);          //PINを入力用に設定
  digitalWrite(LED_LEADER, HIGH);   //PINをOFF
  digitalWrite(LED_OUTPUT, LOW);    //PINをOFF
  digitalWrite(LED_DETECT_1, LOW);  //PINをOFF
  digitalWrite(LED_DETECT_2, LOW);  //PINをOFF
  digitalWrite(LED_DETECT_3, LOW);  //PINをOFF
  digitalWrite(LED_DETECT_0, LOW);  //PINをOFF
  Serial.begin(9600);


  attachInterrupt(SENSOR_IN_1, &DETECT_1, FALLING);  // 光センサ検出割り込み
  attachInterrupt(SENSOR_IN_2, &DETECT_2, FALLING);  // 光センサ検出割り込み

  int ret = MP.begin(1);
  if (ret < 0) {
    MPLog("MP.begin(%d) error = %d\n", 1, ret);
  }
}


// analogReadとタイマ割り込みは同棲できないのでloop-delayで対応
void loop() {

  //ボタンが押された時のlightvalueを記録したい　ボタンがおされるとglobalflagを立てる→　loopごとにflagを確認する　flagが立っていたらanalogreadする

  count = count + 1;
  t = t + 1;

  val1 = digitalRead(button1);  // ボタン押されると0(LOW)押されてないとき1(HIGH)
  val2 = digitalRead(button2);  // ボタン押されると0(LOW)押されてないとき1(HIGH)
  val3 = digitalRead(button3);  // ボタン押されると0(LOW)押されてないとき1(HIGH)

  msg = omega + Domega;

  // シリアルモニタ表示用リセット
  if (count > 100) {
    count = 0;
  }

  // 液晶用転送タイミング
  if (count == 0) {
    MP.Send(MY_MSGID, &msg, 1);
  }

  // リーダー確認用Spresenceライト
  if (L == 0) {
    digitalWrite(LED_DETECT_1, LOW);  //PINをOFF
  } else if (L == 1) {
    digitalWrite(LED_DETECT_1, HIGH);  //PINをON
  }

  // ボタン1が押されたら
  if (val1 == LOW && valold1 == HIGH) {
    // 初めて押されたら点滅開始
    if (state == 0) {
      state = 1;
      phidot = 3.0;
      omega = 3.0;
    }
    // 二回目以降はリセットボタン
    else if (state == 1 || state == 2) {
      state = 0;
      detectflag1 = 0;
      detectflag2 = 0;
      phi = 0;
      phip = 0;
      phidot = 0;
      omega = 3.0;
      digitalWrite(LED_DETECT_0, LOW);
    }
  }

  if (val2 == LOW && valold2 == HIGH) {
    lightValue = analogRead(photoresistorPIN);
    omega = 3.0 + lightValue / 10;
    phidot = omega;
  }



  // ボタン3が押されたら一度リセットし最大値推定へ
  if (val3 == LOW && valold3 == HIGH) {
    state = 2;
    detectflag1 = 0;
    detectflag2 = 0;
    phi = 0;
    phip = 0;
    phidot = omega;
    t = 0;
    digitalWrite(LED_LEADER, LOW);
    digitalWrite(LED_DETECT_0, HIGH);
  }



  // 同期処理の中身
  if (state == 1) {
    phip = phi + phidot * dt;
    phiO = phi;

    // 周期範囲を[-pi pi]にするため
    if (phip >= PI) {
      phi = phip - 2 * PI;
    } else {
      phi = phip;
    }

    //phiが0跨いだら発光
    if (phiO <= 0 && phip > 0) {
      lighttime0 = LED_DURATION;
    }
    /*
      // 両側検知
      if(detectflag1 == 1 && detectflag2 == 1){
         phidot = omega + (sigma*kappa+sigma2*kappa)/2;
         detectflag1 = 0;
         detectflag2 = 0;
      }
      // 片側検知
      else if(detectflag1 == 1 && detectflag2 == 0){
         phidot = omega + (sigma*kappa);
         detectflag1 = 0;
         detectflag2=0;
      }
      else if(detectflag1 == 0 && detectflag2 == 1){
         phidot = omega + (sigma2*kappa);
         detectflag1 = 0;
         detectflag2 = 0;
      }
*/
    // SoresenceのLED点滅表現(おそらくデバック用)
    if (lighttime0 > 0) {
      digitalWrite(LED_OUTPUT, HIGH);  //PINをON
      lighttime0 = lighttime0 - 1;
    } else {
      digitalWrite(LED_OUTPUT, LOW);  //PINをOFF
    }
    if (lighttime1 > 0) {
      digitalWrite(LED_DETECT_2, HIGH);  //PINをON
      lighttime1 = lighttime1 - 1;
    } else {
      digitalWrite(LED_DETECT_2, LOW);  //PINをOFF
    }
    if (lighttime2 > 0) {
      digitalWrite(LED_DETECT_3, HIGH);  //PINをON
      lighttime2 = lighttime2 - 1;
    } else {
      digitalWrite(LED_DETECT_3, LOW);  //PINをOFF
    }
  }

  // 最大値推定処理
  else if (state == 2) {

    phip = phi + (omega + Domega) * dt;

    if (Domega > 0) {
      digitalWrite(LED_LEADER, HIGH);
    }
    phiO = phi;

    // 周期範囲を[-pi pi]にするため
    if (phip >= PI) {
      phi = phip - 2 * PI;
    } else {
      phi = phip;
    }

    //phiが0跨いだら発光
    if (phiO <= 0 && phip > 0) {
      lighttime0 = LED_DURATION;
    }


    // LED点滅表現
    if (lighttime0 > 0) {
      digitalWrite(LED_OUTPUT, HIGH);  //PINをON
      lighttime0 = lighttime0 - 1;
    } else {
      digitalWrite(LED_OUTPUT, LOW);  //PINをOFF
    }
  } else {
    digitalWrite(LED_OUTPUT, LOW);  //PINをOFF
  }

  valold1 = val1;
  valold2 = val2;
  valold3 = val3;

  //Serial.print("D=");
  //Serial.println(count);
  //Serial.print(",");
  //Serial.print("E=");
  // Serial.println(msg);
  // Serial.println(lightValue);
  // Serial.println(Eomega);
  // Serial.println(Domega);

  // Serial.println(timesave1);
  //  Serial.println(timesave2);
  //Serial.println(t);
  //Serial.println("-------------------");


  //Serial.println(state);
  //Serial.print("phidot=");
  //Serial.println(phidot);
  //Serial.print("SI=");
  //Serial.println(sigma);
  //Serial.print(",");
  //Serial.print("SI2=");
  //Serial.println(sigma2);
  //Serial.print("light=");
  //Serial.println(lighttime0);
  //Serial.print("phi=");
  //Serial.println(phi);
  //Serial.print("st=");
  //Serial.println(state);
  //Serial.print("val1=");
  //Serial.println(lightval);
  //Serial.print("val2=");
  //Serial.println(lightval2);
  //Serial.print("dphi=");
  //Serial.println(phidot);
  // Serial.println("  ");
  //}

  Serial.println(lightValue);
  delay(INTERVAL);
}

//
//void loop(){
//}