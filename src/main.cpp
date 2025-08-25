#include <Arduino.h>
#include <ESP32Servo.h> 

Servo myServo;

int ledPin = 8;    // LED connected to digital pin 10
int servoPin = 10;    // Wire S connected to digital pin 10

void setup() {
  // declaring LED pin as output
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  myServo.attach(servoPin);

  // 允许ESP32C3的所有引脚都可用于舵机
  ESP32PWM::allocateTimer(0); // 这行是ESP32Servo库需要的初始化
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myServo.setPeriodHertz(50); // 标准值是50Hz，这意味着每个脉冲周期为20ms
  myServo.attach(servoPin, 1000, 2000); // 设置脉冲宽度范围（微秒
  Serial.println("ESP32Servo library started!");
  Serial.println("Using: 1000-2000us @ 50Hz");
}

void loop() {
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // 控制舵机转到最小角度位置 (1000us脉冲)
  myServo.write(0);
  Serial.println("Position: 0° -> 1000us");
  delay(1000);
  
  // 控制舵机转到中间位置 (1500us脉冲)
  myServo.write(90);
  Serial.println("Position: 90° -> 1500us");
  delay(1000);
  
  // 控制舵机转到最大角度位置 (2000us脉冲)
  myServo.write(180);
  Serial.println("Position: 180° -> 2000us");
  delay(1000);
}