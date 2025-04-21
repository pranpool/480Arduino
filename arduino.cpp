#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
const int buzzerPin = 6;
const int movementThreshold = 20000;  // Adjust as needed
int end1 = 8;
int end2 = 9;
int button = 7;
int state = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(end1,OUTPUT);
  pinMode(end2,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Initializing");

  Wire.begin();
  mpu.initialize();

}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  long totalAccel = abs(ax) + abs(ay) + abs(az);

  // Print raw accelerometer data
  Serial.print("Accel X: "); Serial.print(ax);
  Serial.print(" | Y: "); Serial.print(ay);
  Serial.print(" | Z: "); Serial.print(az);
  Serial.print(" | Total: "); Serial.println(totalAccel);

  if (totalAccel > movementThreshold) {
    Serial.println("Motion detected! Beeping...");

    analogWrite(buzzerPin, 50); //decrease it to lower noise
    delay(500);
    analogWrite(buzzerPin, 0);
    delay(500);
  }
  if((digitalRead(button)==LOW)&&state == 0){
    digitalWrite(end1,HIGH);
    digitalWrite(end2,LOW);
    delay(1000);
    state = 1;
  }else if((digitalRead(button)==LOW)&&state == 1){
    digitalWrite(end1,LOW);
    digitalWrite(end2,HIGH);
    delay(1000);
    state = 0;
  }

  delay(200);  // Regular polling delay
}
