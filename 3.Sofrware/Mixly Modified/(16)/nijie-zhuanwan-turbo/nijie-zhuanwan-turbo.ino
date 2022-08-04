#define dt 45.0  //定义大腿长度
#define xt 50.0  //定义小腿长度

#define x_b -60.0  //轨迹坐标变换x轴
#define y_b 0.0   //轨迹坐标变换y轴

#define pi 3.1415  //圆周率Π
//将轨迹离散化处理后找出替代点的坐标
float xy[36][2]={
  75.0,80.0,
  77.0,78.167,
  79.0,77.485,
  81.0,77.018,
  83.0,76.674,
  85.0,76.416,
  87.0,76.228,
  89.0,76.100,
  91.0,76.024,
  93.0,76.0,
  95.0,76.024,
  97.0,76.100,
  99.0,76.228,
  101.0,76.416,
  103.0,76.674,
  105.0,77.018,
  107.0,77.485,
  109.0,78.167,
  111.0,80.0,
  109.0,80.0,
  107.0,80.0,
  105.0,80.0,
  103.0,80.0,
  101.0,80.0,
  99.0,80.0,
  97.0,80.0,
  95.0,80.0,
  93.0,80.0,
  91.0,80.0,
  89.0,80.0,
  87.0,80.0,
  85.0,80.0,
  83.0,80.0,
  81.0,80.0,
  79.0,80.0,
  77.0,80.0
  };
//小椭圆轨迹
float xy1[36][2]={
  75.0,80.0,
  75.0,78.167,
  75.0,77.485,
  75.0,77.018,
  75.0,76.674,
  75.0,76.416,
  75.0,76.228,
  75.0,76.100,
  75.0,76.024,
  75.0,76.0,
  75.0,76.024,
  75.0,76.100,
  75.0,76.228,
  75.0,76.416,
  75.0,76.674,
  75.0,77.018,
  75.0,77.485,
  75.0,78.167,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0,
  75.0,80.0
  };
//定义角度变量，存储8和12关节舵机角度数据，大椭圆轨迹
float angle[36][2]={
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0
};
//定义角度变量，存储8和12关节舵机角度数据，小椭圆轨迹
float angle1[36][2]={
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0,
  0.0,0.0
};
//主要算法，将文档中的算法公式用程序代码实现。大椭圆轨迹
void sf(){
//变量a,b分别存储8和12号舵机的关节角度数据
//，其他为中间变量，存储计算过程中的数据
  float xb2=0.0,a=0.0,a1=0.0,a2=0.0;
  float b=0.0;
  for(int i=0;i<=35;i++)//对现在坐标进行坐标系变换（平移操作）
  {
    xy[i][0]=xy[i][0]+x_b;
    xy[i][1]=xy[i][1]+y_b;
  }
//具体算法实现，程序反三角函数计算出来的
//角度表示方法为弧度，要切换成角度
  for(int i=0;i<=35;i++)
  {
    xb2=xy[i][0]*xy[i][0]+xy[i][1]*xy[i][1];
    a1=acos((dt*dt+xb2-xt*xt)/(2*sqrt(xb2)*dt))*180/pi;
    a2=atan(xy[i][1]/xy[i][0])*180/pi;
    a=a1+a2-90.0;
    b=acos((dt*dt+xt*xt-xb2)/(2*dt*xt))*180/pi;
    b=b-90.0;
    delay(3);
    angle[i][0]=round(a);
    angle[i][1]=round(b);
  }
}

//主要算法，将文档中的算法公式用程序代码实现。小椭圆轨迹
void sf1(){
//变量a,b分别存储8和12号舵机的关节角度数据
//，其他为中间变量，存储计算过程中的数据
  float xb2=0.0,a=0.0,a1=0.0,a2=0.0;
  float b=0.0;
  for(int i=0;i<=35;i++)//对现在坐标进行坐标系变换（平移操作）
  {
    xy1[i][0]=xy1[i][0]+x_b;
    xy1[i][1]=xy1[i][1]+y_b;
  }
//具体算法实现，程序反三角函数计算出来的
//角度表示方法为弧度，要切换成角度
  for(int i=0;i<=35;i++)
  {
    xb2=xy1[i][0]*xy1[i][0]+xy1[i][1]*xy1[i][1];
    a1=acos((dt*dt+xb2-xt*xt)/(2*sqrt(xb2)*dt))*180/pi;
    a2=atan(xy1[i][1]/xy1[i][0])*180/pi;
    a=a1+a2-90.0;
    b=acos((dt*dt+xt*xt-xb2)/(2*dt*xt))*180/pi;
    b=b-90.0;
    delay(3);
    angle1[i][0]=round(a);
    angle1[i][1]=round(b);
  }
}


//输出右转数据：将角度数据依照每帧8个数据的格式输出，一共36帧
void sc(){//这里因为是对角交错，因此分成两部分对数据处理
  for(int i=0;i<=17;i++)
  {
    Serial.print(int(angle[i][0]),DEC);
    Serial.print(",");
    Serial.print(int(angle1[18+i][0]),DEC);
    Serial.print(",");
    Serial.print(-int(angle1[17-i][0]),DEC);
    Serial.print(",");
    Serial.print(-int(angle[i][0]),DEC);
    Serial.print(",");
    Serial.print(int(angle[i][1]),DEC);
    Serial.print(",");
    Serial.print(int(angle1[18+i][1]),DEC);
    Serial.print(",");
    Serial.print(-int(angle1[17-i][1]),DEC);
    Serial.print(",");
    Serial.print(-int(angle[35-i][1]),DEC);
    Serial.print(",");
    Serial.println();
  }
  for(int i=18;i<=35;i++)
  {
    Serial.print(int(angle[i][0]),DEC);
    Serial.print(",");
    Serial.print(int(angle1[i-18][0]),DEC);
    Serial.print(",");
    Serial.print(-int(angle1[53-i][0]),DEC);
    Serial.print(",");
    Serial.print(-int(angle[i][0]),DEC);
    Serial.print(",");
    Serial.print(int(angle[i][1]),DEC);
    Serial.print(",");
    Serial.print(int(angle1[i-18][1]),DEC);
    Serial.print(",");
    Serial.print(-int(angle1[53-i][1]),DEC);
    Serial.print(",");
    Serial.print(-int(angle[35-i][1]),DEC);
    Serial.print(",");
    Serial.println();
  }
  Serial.println();
}


//输出左转数据：将角度数据依照每帧8个数据的格式输出，一共36帧
void sc1(){//这里因为是对角交错，因此分成两部分对数据处理
  for(int i=0;i<=17;i++)
  {
    Serial.print(int(angle1[i][0]),DEC);
    Serial.print(",");
    Serial.print(int(angle[18+i][0]),DEC);
    Serial.print(",");
    Serial.print(-int(angle[17-i][0]),DEC);
    Serial.print(",");
    Serial.print(-int(angle1[i][0]),DEC);
    Serial.print(",");
    Serial.print(int(angle1[i][1]),DEC);
    Serial.print(",");
    Serial.print(int(angle[18+i][1]),DEC);
    Serial.print(",");
    Serial.print(-int(angle[17-i][1]),DEC);
    Serial.print(",");
    Serial.print(-int(angle1[35-i][1]),DEC);
    Serial.print(",");
    Serial.println();
  }
  for(int i=18;i<=35;i++)
  {
    Serial.print(int(angle1[i][0]),DEC);
    Serial.print(",");
    Serial.print(int(angle[i-18][0]),DEC);
    Serial.print(",");
    Serial.print(-int(angle[53-i][0]),DEC);
    Serial.print(",");
    Serial.print(-int(angle1[i][0]),DEC);
    Serial.print(",");
    Serial.print(int(angle1[i][1]),DEC);
    Serial.print(",");
    Serial.print(int(angle[i-18][1]),DEC);
    Serial.print(",");
    Serial.print(-int(angle[53-i][1]),DEC);
    Serial.print(",");
    Serial.print(-int(angle1[35-i][1]),DEC);
    Serial.print(",");
    Serial.println();
  }
  Serial.println();
}
void setup() {
  Serial.begin(57600);
  sf();//计算轨迹离散化之后的舵机角度偏差值
  sf1();//计算轨迹离散化之后的舵机角度偏差值
  sc();//输出右转数据
  Serial.println();//输出右转数据之后，空4行
  Serial.println();
  Serial.println();
  Serial.println();
  sc1();//输出左转数据
}

void loop() {
}
