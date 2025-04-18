#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
const int buzzerPin = 6;
const int movementThreshold = 20000;  // Adjust as needed

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing I2C and MPU6050...");

  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("Error: MPU6050 connection failed.");
    while (1);  // Stop execution if MPU not found
  } else {
    Serial.println("MPU6050 connected successfully.");
  }

  pinMode(buzzerPin, OUTPUT);
  Serial.println("Setup complete. Monitoring for movement...");
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

  delay(200);  // Regular polling delay
}

