#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;


// =====================================================
// LED PINS
// =====================================================

#define BLUE_LED   13
#define GREEN_LED  14
#define RED_LED    26


// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);

  // LED pins
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Turn everything OFF initially
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);


  // =================================================
  // ESP32 I2C
  // =================================================

  Wire.begin(21, 22);


  // =================================================
  // MPU6050
  // =================================================

  if (!mpu.begin())
  {
    Serial.println("MPU6050 not found!");

    while (1)
    {
      delay(10);
    }
  }

  Serial.println("MPU6050 found!");


  // Accelerometer ±2g
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);

  // Gyroscope ±250°/s
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);

  // Low-pass filter
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(500);

  Serial.println("Motion LED system ready!");
}


// =====================================================
// LOOP
// =====================================================

void loop()
{
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;

  // Read MPU6050
  mpu.getEvent(&accel, &gyro, &temp);


  // =================================================
  // ACCELEROMETER
  // =================================================

  float ax = accel.acceleration.x;
  float ay = accel.acceleration.y;
  float az = accel.acceleration.z;


  // Total acceleration magnitude

  float accelerationMagnitude =
      sqrt(
        ax * ax +
        ay * ay +
        az * az
      );


  // Remove gravity

  float dynamicAcceleration =
      fabs(accelerationMagnitude - 9.81);


  // Convert to g

  float dynamicAccelerationG =
      dynamicAcceleration / 9.81;


  // =================================================
  // GYROSCOPE
  // =================================================

  // Library gives rad/s

  float gx =
      gyro.gyro.x * 180.0 / PI;

  float gy =
      gyro.gyro.y * 180.0 / PI;

  float gz =
      gyro.gyro.z * 180.0 / PI;


  // Total angular velocity

  float rotationMagnitude =
      sqrt(
        gx * gx +
        gy * gy +
        gz * gz
      );


  // =================================================
  // MOTION SCORE
  // =================================================

  // Convert acceleration and rotation
  // into comparable scores.

  float accelerationScore =
      dynamicAccelerationG / 1.0 * 100.0;

  float rotationScore =
      rotationMagnitude / 180.0 * 100.0;


  // Use whichever is stronger

  float motionScore =
      max(accelerationScore, rotationScore);


  // Limit score to 0-100

  motionScore =
      constrain(motionScore, 0, 100);


  // =================================================
  // LED LOGIC
  // =================================================

  // First turn everything OFF

  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);


  // LOW MOTION → BLUE

  if (motionScore > 5)
  {
    digitalWrite(BLUE_LED, HIGH);
  }


  // MEDIUM MOTION → GREEN

  if (motionScore > 30)
  {
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }


  // HIGH MOTION → RED

  if (motionScore > 70)
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }


  // =================================================
  // SERIAL MONITOR
  // =================================================

  Serial.print("Acceleration: ");
  Serial.print(dynamicAccelerationG, 2);
  Serial.print(" g");

  Serial.print(" | Rotation: ");
  Serial.print(rotationMagnitude, 1);
  Serial.print(" °/s");

  Serial.print(" | Motion Score: ");
  Serial.print(motionScore, 1);

  Serial.println();


  delay(20);
}