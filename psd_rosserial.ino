/*
・SHARPの距離センサ GP2Y0A21YK0F のプログラム
・1秒ごとに距離を測定し、シリアルモニタに出力
・Arduinoとの接続
     ・Vo（白）       アナログ入力 A0
     ・GND（黄色）    GND
     ・Vcc（黒）      5V
*/
/*
・SHARPの距離センサ GP2Y0A21YK0F のプログラム
・1秒ごとに距離を測定し、シリアルモニタに出力
・Arduinoとの接続
     ・Vo（白）       アナログ入力 A0
     ・GND（黄色）    GND
     ・Vcc（黒）      5V
*/

#include <ros.h>
#include <std_msgs/Float32.h>

const int analogInPin = A0;    // アナログ入力ピン（定数）
const float Vcc = 5.0;         // 電源電圧（定数）
int   ad;                      // AD値（変数）
float dist;                    // 距離（変数）

ros::NodeHandle nh;
std_msgs::Float32 ad_msg;
std_msgs::Float32 dist_msg;
ros::Publisher chatter1("ad", &ad_msg);
ros::Publisher chatter2("distance", &dist_msg);

void setup()
{
  //Serial.begin(9600);         // シリアルモニタを開始
  nh.initNode();
  nh.advertise(chatter1);
  nh.advertise(chatter2);
  
}

void loop()
{
  ad = analogRead(analogInPin);         // AD値を取得
  dist = Vcc * ad / 1023;  
  dist = 26.548 * pow(dist, -1.209);   // 距離を計算
  /*Serial.print("AD = ");
  Serial.print(ad);
  Serial.print(" , ");
  Serial.print("Dist = ");
  Serial.print(dist);
  Serial.println(" cm");*/
  ad_msg.data = ad;
  chatter1.publish(&ad_msg);
  dist_msg.data = dist;
  chatter2.publish(&dist_msg);
  nh.spinOnce();
  delay(1000);
  
}
