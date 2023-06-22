#include <cstdint>
#include <cmath>
#include <stdio.h>
#include "arduino.h"

//----設定パラメータ---------------------
//String min_step="0085";//観測開始方向
//String max_step="0603";//観測終了方向 
//青
String min_step="0118";//観測開始方向
String max_step="0636";//観測終了方向 
String skip_step="16";//間引く方向数

//-------------------------------------

double distance[1536];//観測データ
int timer3=0;
double distance_1[1536];//1ステップ前の観測データ
double distance_r[3072];
double distance_xy[3072];//座標変換後の観測データ
double u2[4];
double u4[4];

double* get_distance(String max_step,String min_step,String measure_step){//LiDARからのデータ受信、座標変換を行う
  int index=47;//距離データ部分の開始地点
  int index2=0;//読み取ったデータ数カウント
  int index3=41;//タイムスタンプ開始地点
  int NUMBER_OF_STEP=768;//LiDARのステップ開始地点
  int start_step =min_step.toInt();//文字列の数値変換
  int stop_step =max_step.toInt();
  int me_step=measure_step.toInt();
  int x=0;
  String r;
  int32_t timer=0;
  int timer2=0;
  int count=0;
  char val[2048]={0};//文字列格納配列
  String sendmessage="MD"+min_step+max_step+measure_step+"001\r\n";//LIDARに送る文字列
  Serial2.write(sendmessage.c_str());
  while(Serial2.available() > 0){//LIDARからのデータ読み取り
   val[count]= Serial2.read();  
   count=count+1;
  }  
  //delay(50);
  //Serial.print(val);
  for (int d = 0; d<4; d++){//タイムスタンプのデコード
        timer = val[index3]-0x30;
        x=6*(3-d);
        while (timer != 0){
            r += ( timer % 2 == 0 ? "0" : "1" );
            timer /= 2;
        }
        for (int c =0; c<6;c++){
          if(r[c]=='1'){
              timer2=timer2+std::pow(2, x);
          }
          x=x+1;
        }
        r="";
        index3=index3+1;
    }
  for (int step = 0; step<NUMBER_OF_STEP; step++){//距離データのデコード
    if (step < start_step || step > stop_step){//観測範囲外のデータを65535に
      distance[step] = 65535;
      continue;
    }
    if ((step-start_step)%me_step!=0){//間引いた方向のデータを65535に
      distance[step] = 65535;
      continue;
    }
    int32_t dist = 0;
    int dist2 = 0;
    for (int d = 0; d<3; d++){
     dist = val[index]-0x30;
     x=6*(2-d);
     while (dist != 0){
      r += ( dist % 2 == 0 ? "0" : "1" );
      dist /= 2;
     }
     for (int c =0; c<6;c++){
      if(r[c]=='1'){
        dist2=dist2+std::pow(2, x);
      }
      x=x+1;
      }
      r="";
      index=index+1;
      index2=index2+1;
      if(index2 == 64){
        index = index+2;
        index2 = 0;
      }
      if(val[index] == '\n'){
        index++;
        index2 = 0;
      }
  }
      distance[step] = (double)dist2;
      if(distance[step] == 0){//観測できていない方向のデータを65535に
        distance[step] = 65535;
      }
 }
 for (int step = 0; step<NUMBER_OF_STEP; step++){//相対速度のデータ作成
    if (distance_1[step]==65535){
      distance[step+768] = 0;
      continue;
    }
    distance[step+768]=1000*(distance[step]-distance_1[step])/(timer2-timer3);
 }
 for (int step = 0; step<NUMBER_OF_STEP*2; step++){
 distance_1[step]=distance[step];
 }
 timer3=timer2;
 for (int step = 0; step<NUMBER_OF_STEP; step++){//座標変換 (596ステップ目をx軸方向に)
 distance_r[step]=distance[step]*cos((step-596)*2*M_PI/1024);
 distance_r[step+768]=distance[step]*sin((step-596)*2*M_PI/1024);
 distance_r[step+768*2]=distance[step+768]*cos((step-596)*2*M_PI/1024);
 distance_r[step+768*3]=distance[step+768]*sin((step-596)*2*M_PI/1024);
 }
 return distance_r;
}

double* One_CBF(double q1,double dq1,double q2,double dq2,double u,double houkou){//入力の再設計を行う関数
  double gamma=2;//CBFの制約パラメータɤ
  double dt=0.2;//時定数(delay(200)なので0.2)
  
  double r=200;//安全距離(mm)
  u2[1]=0;
  double forward_constrain = dq1*q1/abs(q1)-2*u*dt*q1/abs(q1)+gamma*(abs(q1)+dq1*q1/abs(q1)*dt-r);
  double behind_constrain = dq2*q2/abs(q2)-2*u*dt*q2/abs(q2)+gamma*(abs(q2)+dq2*q2/abs(q2)*dt-r);
  if(forward_constrain>=0 && behind_constrain>=0){
    u2[0]=u;
  }
  else if(!(forward_constrain>=0) && behind_constrain>=0){
    u2[0]=(dq1*q1/abs(q1)+gamma*(abs(q1)+dq1*q1/abs(q1)*dt-r))/(2*dt*q1/abs(q1));
  }
  else if(forward_constrain>=0 && !(behind_constrain>=0)){
    u2[0]=(dq2*q2/abs(q2)+gamma*(abs(q2)+dq2*q2/abs(q2)*dt-r))/(2*dt*q2/abs(q2));
  }  
  else{
    u2[0]=0;
    u2[1]=1;
  }
  u2[2]=(dq1*q1/abs(q1)+gamma*(abs(q1)+dq1*q1/abs(q1)*dt-r))/(2*dt*q1/abs(q1));
  u2[3]=(dq2*q2/abs(q2)+gamma*(abs(q2)+dq2*q2/abs(q2)*dt-r))/(2*dt*q2/abs(q2));
  return u2;
}

double* One_CBFasym(double q1,double dq1,double q2,double dq2,double u,double v,double houkou){//入力の再設計を行う関数
<<<<<<< HEAD
  double gamma=0.8;//CBFの制約パラメータɤ
  double dt=0.1;//時定数(delay(200)なので0.2)
  double r=350;//安全距離(mm)
  if(houkou==0){
    v=-v;
  }
=======
  double gamma=0.5;//CBFの制約パラメータɤ
double dt=0.1;//時定数(delay(200)なので0.2)
double r=400;//安全距離(mm)
if(houkou==0){
  v=-v;
}
>>>>>>> origin/ETCHU
  u2[1]=0;
  double forward_constrain = -2*v*q1/abs(q1)-2*u*dt*q1/abs(q1)+gamma*(abs(q1)-2*v*q1*dt/abs(q1)-r);
  double behind_constrain =  -2*v*q2/abs(q2)-2*u*dt*q2/abs(q2)+gamma*(abs(q2)-2*v*q2*dt/abs(q2)-r);
  if(forward_constrain>=0 && behind_constrain>=0){
    u2[0]=u;
  }
  else if(!(forward_constrain>=0) && behind_constrain>=0){
    u2[0]=(-2*v*q1/abs(q1)+gamma*(abs(q1)-2*v*q1/abs(q1)*dt-r))/(2*dt*q1/abs(q1));
  }
  else if(forward_constrain>=0 && !(behind_constrain>=0)){
    u2[0]=(-2*v*q2/abs(q2)+gamma*(abs(q2)-2*v*q2/abs(q2)*dt-r))/(2*dt*q2/abs(q2));
  }  
  else{
    u2[0]=-(gamma+1/dt)*dq1;
    u2[1]=1;
  }
  u2[2]=(-2*v*q1/abs(q1)+gamma*(abs(q1)-2*v*q1/abs(q1)*dt-r))/(2*dt*q1/abs(q1));
  u2[3]=(-2*v*q2/abs(q2)+gamma*(abs(q2)-2*v*q2/abs(q2)*dt-r))/(2*dt*q2/abs(q2));
  return u2;
}

double* CBF1D(double u,double houkou){
  double* ptr;
  double* ptr2;
  ptr= get_distance(max_step, min_step,skip_step);   
  for (int i = 0; i < 3072; ++i) {
    distance_xy[i]=ptr[i];
  }
  ptr2= One_CBF(distance_xy[min_step.toInt()],distance_xy[min_step.toInt()+1536],distance_xy[min_step.toInt()+512],distance_xy[min_step.toInt()+2048],u,houkou);
  for (int i = 0; i < 4; ++i) {
    u4[i]=ptr2[i];
  }
  return u4;
}
double* CBF1Dasym(double u,double v,double houkou){
  double* ptr;
  double* ptr2;
  ptr= get_distance(max_step, min_step,skip_step);   
  for (int i = 0; i < 3072; ++i) {
    distance_xy[i]=ptr[i];
  }
  ptr2= One_CBFasym(distance_xy[min_step.toInt()],distance_xy[min_step.toInt()+1536],distance_xy[min_step.toInt()+512],distance_xy[min_step.toInt()+2048],u,v,houkou);
  for (int i = 0; i < 4; ++i) {
    u4[i]=ptr2[i];
  }
  return u4;
}
