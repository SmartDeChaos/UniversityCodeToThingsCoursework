#include <SoftwareSerial.h>
#include <Stepper.h>
#define STEPS 100
Stepper stepper(STEPS, 8, 10, 9, 11);//引脚要互换
SoftwareSerial BTSerial(2,3);

//设置步进电机的步数和引脚（就是注意点2里面说的驱动板上IN1～IN4连接的四个数字口）。

String comdata = "";

void setup() {
  // 设置电机的转速：每分钟为90步
  stepper.setSpeed(90);
  // 初始化串口，用于调试输出信息
  Serial.begin(9600);
  Serial.println("WHY I'M STILL ALIVE");
  BTSerial.begin(9600);
}
void loop() {
if(Serial.available()){
   BTSerial.write(Serial.read());
   //Serial.write(Serial.read());
  }
  if(BTSerial.available()){   
      while (BTSerial.available() > 0)  
    {
        comdata += char(BTSerial.read());
        delay(2);
    }
    if (comdata == "1")//1:start
    {
      Serial.println("shun");
        shun();
    }else if(comdata == "2")
    {
       Serial.println("ni");
       ni();
    }
    if (comdata.length() > 0)
    {
        Serial.println(comdata);
        comdata = "";
    }
    }  
}

void shun()
{
    // 顺时针旋转一周
    Serial.println("shun");
   stepper.step(1024);  //4步模式下旋转一周用2048 步。
    delay(500);

}
void ni()
{
    // 逆时针旋转半周
    Serial.println("ni");
    stepper.step(-1024); //4步模式下旋转一周用2048 步。
    delay(500);
}
