#include<Wire.h>
 
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;
 
void setup(){
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  
  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);
 
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
 
  serialPrint();

  check(x, 13, 12);
  check(y, 11, 10);
  check(z, 9, 8);
  
  delay(1000);
}

void check(int number, int positive, int negative){
  if (number >= 359 || number <= 1)
  {
    digitalWrite(positive, HIGH);
    digitalWrite(negative, LOW);
  }
  else
  {
    digitalWrite(negative, HIGH);
    digitalWrite(positive, LOW);
  }
}

void serialPrint(){
  Serial.print("AngleX= ");
  Serial.println(x);
 
  Serial.print("AngleY= ");
  Serial.println(y);
 
  Serial.print("AngleZ= ");
  Serial.println(z);
  Serial.println("-----------------------------------------");
}
