#include <Mouse.h>
#include <Wire.h>
#include <MPU6050.h>
int count=0;

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;

void setup() 
{
  Serial.begin(9600);
  pinMode(4, INPUT_PULLUP);  // LEFT CLICK
  pinMode(2, INPUT_PULLUP);  // RIGHT CLICK
  pinMode(3, INPUT_PULLUP);  // MIDDLE CLICK
  while (!Serial) ; // unless serial cable is connected, do nothing
  delay(4000);  // additional delay
  Serial.println("Hello, code start");
  Wire.begin(); Serial.println("I2C begin");
  mpu.initialize(); Serial.println("MPU Sensor Initializing...");
  if (!mpu.testConnection()) { while (1); }   // wait here infinitely till sensor initializes. 
  
  Serial.println("Sensor initialized");
}

void loop() 
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  vx = -(gx+260)/150;  // change 300 from 0 to 355
  vy = (gz+100)/150; // same here about "-100"  from -355 to 0

  Serial.print("gx = ");
  Serial.print(gx);
  Serial.print(" | gz = ");
  Serial.print(gz);
  
  Serial.print("        | X = ");
  Serial.print(vx);
  Serial.print(" | Y = ");
  Serial.println(vy); 

  int buttonState1 = digitalRead(4); // Check left click
  int buttonState3 = digitalRead(3); // Check middle click
  int buttonState2 = digitalRead(2); // check right click

  if (buttonState3 == LOW) {
    Mouse.press(MOUSE_MIDDLE);
    delay(100);
    Mouse.release(MOUSE_MIDDLE);
    delay(200);
  }
  else if (buttonState1 == LOW) {
    Mouse.press(MOUSE_LEFT);
    delay(100);
    Mouse.release(MOUSE_LEFT);
    delay(200);
  }
  else if (buttonState2 == LOW) {
    Mouse.press(MOUSE_RIGHT);
    delay(100);
    Mouse.release(MOUSE_RIGHT);
    delay(200);
  }
  
  Mouse.move(vx, vy);

    
  delay(20);
}