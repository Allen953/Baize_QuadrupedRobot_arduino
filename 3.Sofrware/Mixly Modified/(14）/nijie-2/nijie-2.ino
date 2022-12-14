#include <Wire.h>                      //IIC通讯头文件
#include <Adafruit_PWMServoDriver.h> //16路舵机控制板头文件
//以这种方式调用，它使用默认地址0x40。
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  680   //这是“最小”高电平占空比计数（在4096中）
#define SERVOMAX  2200   //这是“最大”高电平占空比计数（在4096中）
//前进步态帧数据
char wk[36][8]= {
22,30,-30,-30,28,30,-30,-30,
22,30,-30,-30,25,30,-30,-30,
21,30,-30,-30,24,30,-30,-30,
20,30,-30,-30,24,30,-30,-30,
18,30,-30,-30,25,30,-30,-30,
16,30,-30,-30,26,30,-30,-30,
14,30,-30,-30,27,30,-30,-30,
12,30,-30,-30,28,30,-30,-30,
10,30,-30,-30,29,30,-30,-30,
8,30,-30,-30,31,30,-30,-30,
5,30,-30,-30,33,30,-30,-30,
3,30,-30,-30,36,30,-30,-30,
0,30,-30,-30,39,30,-30,-30,
-3,30,-30,-30,42,30,-30,-30,
-6,30,-30,-30,45,30,-30,-30,
-9,30,-30,-30,50,30,-30,-30,
-13,30,-30,-30,55,30,-30,-30,
-18,30,-30,-30,62,30,-30,-30,
-29,30,-30,-30,84,30,-30,-30,
-22,30,-30,-30,72,30,-30,-30,
-17,30,-30,-30,65,30,-30,-30,
-14,30,-30,-30,60,30,-30,-30,
-10,30,-30,-30,56,30,-30,-30,
-7,30,-30,-30,52,30,-30,-30,
-4,30,-30,-30,49,30,-30,-30,
-2,30,-30,-30,46,30,-30,-30,
1,30,-30,-30,44,30,-30,-30,
3,30,-30,-30,41,30,-30,-30,
6,30,-30,-30,39,30,-30,-30,
8,30,-30,-30,37,30,-30,-30,
10,30,-30,-30,35,30,-30,-30,
12,30,-30,-30,34,30,-30,-30,
14,30,-30,-30,32,30,-30,-30,
17,30,-30,-30,31,30,-30,-30,
18,30,-30,-30,30,30,-30,-30,
20,30,-30,-30,29,30,-30,-30
};
//舵机校准偏角数据
char cal[16]={-6,-14,7,0,0,0,0,0,1,9,-3,3,6,-6,7,-6};
//舵机旋转方向
int8_t rotationDirections[] = {1, -1, 1, 1,
                               1, -1, 1, -1,
                               1, -1, -1, 1,
                               -1, 1, 1, -1
                              };
//关节映射表
byte pins[] = {4, 3, 11, 12,
               5, 2, 13, 10,
               6, 1, 14, 9,
               7, 0, 15, 8
              };
//将角度数据转换成高电平占空比
int S2P(int angle){
  float p=0.0;
  p=(1520/150)*angle+680+760;
  return int(p);
}

void setup() {
   Serial.begin(57600);//打开串口
   pwm.begin();       //初始化PCA9685
   pwm.setPWMFreq(240);  //设置频率60Hz  
}

void loop() {
  //循环一次前进步态
  for(int i=0;i<=35;i++)//一共43帧
  {
    for(int j=0;j<=7;j++)//每帧8个舵机角度
    {      
      Serial.print(int(wk[i][j]));
      //具体舵机角度=步态帧中舵机角度数据*旋转方向+舵机校准偏角+75
      //每次从8号关节舵机开始，执行到16号关节舵机，为一帧
      pwm.setPWM(pins[8+j],0,S2P((int(wk[i][j])+cal[8+j])*rotationDirections[j+8]));
      Serial.print(',');
    }
    delay(20);
    Serial.println();
  }
  //delay(1000);//只执行一次，如果想循环执行，则需要将此行注释掉
}
