//  --------                 --------
// |  D9    |               |  D7    |
// | joint9 |               | joint7 |
//  ----- --------     --------- -----
//       |  D8    |   |  D6    |
//       | joint8 |   | joint6 |
//        --------     --------
//       |  D2    |  |   D4    |
//       | joint2 |  |  joint4 |
//  ----- --------    --------- -----
// |  D3    |               |  D5    |
// | joint3 |               | joint5 |
//  --------                 --------
//                Front



#include <Servo.h>

// サーボ宣言
Servo joint2;  // 右前ヒップ
Servo joint3;  // 右前レッグ
Servo joint4;  // 左前ヒップ
Servo joint5;  // 左前レッグ
Servo joint6;  // 左後ヒップ
Servo joint7;  // 左後レッグ
Servo joint8;  // 右後ヒップ
Servo joint9;  // 右後レッグ
Servo neck_servo;  // ネックサーボ

// ホームポジション
int home_joint2 = 120;
int home_joint3 = 15;
int home_joint4 = 60;
int home_joint5 = 165;
int home_joint6 = 100;
int home_joint7 = 15;
int home_joint8 = 70;
int home_joint9 = 165;

// ネックサーボ
#define neck_survoPin 10
#define trigPin 11
#define echoPin 12

float Dulation = 0;
float Distance = 0;
int angle = 90;
int sum = 0;


void setup(){

  joint2.attach(2);
  joint3.attach(3);
  joint4.attach(4);
  joint5.attach(5);
  joint6.attach(6);
  joint7.attach(7);
  joint8.attach(8);
  joint9.attach(9);

  neck_servo.attach(neck_survoPin, 500, 2400);
  neck_servo.write(90);
  
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);

  joint2.write(home_joint2);
  joint3.write(home_joint3);
  joint4.write(home_joint4);
  joint5.write(home_joint5);
  joint6.write(home_joint6);
  joint7.write(home_joint7);
  joint8.write(home_joint8);
  joint9.write(home_joint9);

  delay(3000);

}


void loop(){

  standhome();
  forward(1);


// 超音波センサ使用
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  Dulation = pulseIn(echoPin,HIGH);

  if(Dulation>0){
    int Distance = Dulation*340*100/2/1000000;

    if(Distance < 10){
      int right = 0;
      int left = 0;
      int sumright = 0;
      int sumleft = 0;
      
      int i = 170;
      delay(10);
      while(i >= 120){
        neck_servo.write(i);
        i=i-2;
        digitalWrite(trigPin,LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin,HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin,LOW);
        Dulation = pulseIn(echoPin,HIGH);
        int Distance = Dulation*340*100/2/1000000;
        
        if(Distance <15){
          left = 1;
          sumleft++;
        }else {
            left = 0;
          }
          delay(10);           
      }
      
     i =10;
     delay(10);
     while(i <= 60){
        neck_servo.write(i);
        i=i+2;
        digitalWrite(trigPin,LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin,HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin,LOW);
        Dulation = pulseIn(echoPin,HIGH);
        int Distance = Dulation*340*100/2/1000000;

        if(Distance <15){
          right = 1;
          sumright++;
        }else {
          right = 0;
        }
          delay(10);       
     }


     neck_servo.write(90);
     delay(10);

      if(sumright > sumleft){
      leftturn(3);     
     } else {
      rightturn(3);
     }

     if(sumright >= 20){
      backward(3);
      leftturn(3);
     } else if(sumleft >= 20){
      backward(3);
      rightturn(3);
     }  
   }
}
delay(10);

}


// アイドルタイム
void idle(){
  delay(100);
  }


// ホーム立ち位置
void standhome(){
  joint2.write(home_joint2);
  joint3.write(home_joint3);
  joint4.write(home_joint4);
  joint5.write(home_joint5);
  joint6.write(home_joint6);
  joint7.write(home_joint7);
  joint8.write(home_joint8);
  joint9.write(home_joint9);
}


// 腕を伸ばし地面に接地
void sithome(){
    joint2.write(135);
    joint3.write(65);
    joint4.write(45);
    joint5.write(110);
    joint6.write(135);
    joint7.write(80);
    joint8.write(45);
    joint9.write(110);
}


// 起き上がる動作1
void stand1(){
  sithome();
  joint2.write(170);
  delay(300);
  joint2.write(home_joint2);
  delay(300);
  joint4.write(10);
  delay(300);
  joint4.write(home_joint4);
  delay(300);
  joint6.write(170);
  delay(300);
  joint6.write(home_joint6);
  delay(300);
  joint8.write(10);
  delay(300);
  joint8.write(home_joint8);
  delay(300);
  
  joint3.write(home_joint3);
  joint5.write(home_joint5);
  joint7.write(home_joint7);
  joint9.write(home_joint9);
}


// 起き上がる動作2
void stand2(){
  sithome();
  joint2.write(175);
  joint4.write(5);
  joint6.write(175);
  joint8.write(5);
  delay(600);
    
  joint2.write(home_joint2);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  joint8.write(home_joint8);
  delay(600);
  
  joint3.write(home_joint3);
  joint5.write(home_joint5);
  joint7.write(home_joint7);
  joint9.write(home_joint9);
}


// 起き上がる動作3
void stand3(){ 
  sithome();
  int i;
  int j = 90;
  int k = 90;
  joint2.write(home_joint2);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  joint8.write(home_joint8);
  for(i = 90; i < 165; i++)
  {
    joint5.write(i);
    j = j - 1;
    joint3.write(j);
    delay(20);
  }
  
  for(i = 115; i < 165; i++)
  {
    joint9.write(i);
    k = k - 1;
    joint7.write(k);
    delay(20);
  }
}


// 素早くアップダウン
void downaction(unsigned int step){
  while (step-- > 0){
  sithome();
  delay(100);
  standhome();
  delay(100);
  }
}


// 手を振る
void wink(unsigned int step){
  standhome();
  joint9.write(home_joint9-30);
  
  while (step-- > 0){
  joint5.write(30);
  joint4.write(home_joint4 + 60);
  delay(300);
  joint4.write(home_joint4 - 60);
  delay(300);
  }
}


// 体をクネクネ動かす
void twist(){
  joint3.write(home_joint3);
  joint5.write(home_joint5);
  joint7.write(home_joint7);
  joint9.write(home_joint9);
  
  for(int right=90;right<170;right++){
      joint2.write(right);
      joint6.write(right);
      joint4.write(right-90);
      joint8.write(right-90);
      delay(10);
  }

   for(int right=170;right>90;right--){
      joint2.write(right);
      joint6.write(right);
      joint4.write(right-90);
      joint8.write(right-90);
      delay(10);
  }

}


// 前進(ステップ数)
void forward(unsigned int step){
  while (step-- > 0){
  joint3.write(home_joint3+30);
  joint7.write(home_joint7+30);
  delay(100);
  joint2.write(home_joint2+30);
  joint8.write(home_joint8-30);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  delay(100);
  joint3.write(home_joint3);
  joint7.write(home_joint7);
  idle();
  
  joint5.write(home_joint5-30);
  joint9.write(home_joint9-30);
  delay(100);
  joint2.write(home_joint2);
  joint8.write(home_joint8);
  joint4.write(home_joint4-30);
  joint6.write(home_joint6+30);
  delay(100);
  joint5.write(home_joint5);
  joint9.write(home_joint9);
  idle();
  }
}


// 後退(ステップ数)
void backward(unsigned int step){
  while (step-- > 0){
  joint3.write(home_joint3+30);
  joint7.write(home_joint7+30);
  delay(100);
  joint2.write(home_joint2);
  joint8.write(home_joint8);
  joint4.write(home_joint4-30);
  joint6.write(home_joint6+30);
  delay(100);
  joint3.write(home_joint3);
  joint7.write(home_joint7);
  idle();
  
  joint5.write(home_joint5-30);
  joint9.write(home_joint9-30);
  delay(100);
  joint2.write(home_joint2+30);
  joint8.write(home_joint8-30);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  delay(100);
  joint5.write(home_joint5);
  joint9.write(home_joint9);
  idle();
  }
}


// 右回り(ステップ数)
void rightturn(unsigned int step){
  neck_rightrotate();
  while (step-- > 0){
  joint5.write(home_joint5-30);
  joint9.write(home_joint9-30);
  delay(100);
  joint2.write(home_joint2+30);
  joint8.write(home_joint8-30);
  joint4.write(home_joint4-30);
  joint6.write(home_joint6+30);
  delay(100);
  joint5.write(home_joint5);
  joint9.write(home_joint9);
  idle();
  
  joint3.write(home_joint3+30);
  joint7.write(home_joint7+30);
  delay(100);
  joint2.write(home_joint2);
  joint8.write(home_joint8);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  delay(100);
  joint3.write(home_joint3);
  joint7.write(home_joint7);
  idle();
  }
  neck_home();
}


// 左回り(ステップ数)
void leftturn(unsigned int step){
  neck_leftrotate();
  while (step-- > 0){
  joint3.write(home_joint3+30);
  joint7.write(home_joint7+30);
  delay(100);
  joint2.write(home_joint2+30);
  joint8.write(home_joint8-30);
  joint4.write(home_joint4-30);
  joint6.write(home_joint6+30);
  delay(100);
  joint3.write(home_joint3);
  joint7.write(home_joint7);
  idle();
  
  joint5.write(home_joint5-30);
  joint9.write(home_joint9-30);
  delay(100);
  joint2.write(home_joint2);
  joint8.write(home_joint8);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  delay(100);
  joint5.write(home_joint5);
  joint9.write(home_joint9);
  idle();
  }
  neck_home();
}


// 首を左右に動かす(センサーはOFF)
void neckrotate(){
  int i=90;
  while(i < 150){
    neck_servo.write(i);
    i++;
    delay(5);
  }
  while(i > 30){
    neck_servo.write(i);
    i--;
    delay(5);
  }
  while(i <= 90){
    neck_servo.write(i);
    i++;
    delay(5);
  }
}


// 首を左に回す
void neck_leftrotate(){
  int i=90;
  while(i < 150){
    neck_servo.write(i);
    i++;
    delay(5);
  }
}


// 首を右に回す
void neck_rightrotate(){
  int i=90;
  while(i > 30){
    neck_servo.write(i);
    i--;
    delay(5);
  }
}


// 首ホームポジション
void neck_home(){
  neck_servo.write(90);
}
