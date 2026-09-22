#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

// Gyroscope angle estimates
float gyroPitch = 0;
float gyroRoll = 0;
float gyroYaw = 0;

// Gyroscope offsets
float gyroX_offset = 0;
float gyroY_offset = 0;
float gyroZ_offset = 0;

unsigned long previousTime;


// =====================================================
// GYROSCOPE CALIBRATION
// =====================================================

void calibrateGyroscope()
{
  const int samples = 1000;

  float sumX = 0;
  float sumY = 0;
  float sumZ = 0;

  Serial.println();
  Serial.println("================================");
  Serial.println("GYROSCOPE CALIBRATION");
  Serial.println("Keep the MPU6050 COMPLETELY STILL!");
  Serial.println("================================");

  delay(1000);

  for (int i = 0; i < samples; i++)
  {
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;

    mpu.getEvent(&accel, &gyro, &temp);

    // Library gives gyro in rad/s
    // Convert to deg/s

    float gx = gyro.gyro.x * 180.0 / PI;
    float gy = gyro.gyro.y * 180.0 / PI;
    float gz = gyro.gyro.z * 180.0 / PI;

    sumX += gx;
    sumY += gy;
    sumZ += gz;

    delay(2);
  }

  gyroX_offset = sumX / samples;
  gyroY_offset = sumY / samples;
  gyroZ_offset = sumZ / samples;

  Serial.println();
  Serial.println("Calibration complete!");

  Serial.print("X Offset: ");
  Serial.print(gyroX_offset, 4);
  Serial.println(" °/s");

  Serial.print("Y Offset: ");
  Serial.print(gyroY_offset, 4);
  Serial.println(" °/s");

  Serial.print("Z Offset: ");
  Serial.print(gyroZ_offset, 4);
  Serial.println(" °/s");

  Serial.println();
}


// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);

  // ESP32 I2C
  Wire.begin(21, 22);

  // Initialize MPU6050
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

  delay(100);

  // Calibrate gyro
  calibrateGyroscope();

  previousTime = micros();

  Serial.println("Ready!");
  Serial.println();
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

  // Convert m/s² → g

  float ax_g = ax / 9.80665;
  float ay_g = ay / 9.80665;
  float az_g = az / 9.80665;


  // =================================================
  // GYROSCOPE
  // =================================================

  // Convert rad/s → deg/s

  float gx = gyro.gyro.x * 180.0 / PI;
  float gy = gyro.gyro.y * 180.0 / PI;
  float gz = gyro.gyro.z * 180.0 / PI;

  // Remove gyro bias

  gx -= gyroX_offset;
  gy -= gyroY_offset;
  gz -= gyroZ_offset;


  // =================================================
  // TIME
  // =================================================

  unsigned long currentTime = micros();

  float dt =
      (currentTime - previousTime) / 1000000.0;

  previousTime = currentTime;


  // =================================================
  // ACCELEROMETER ANGLES
  // =================================================

  float accelRoll =
      atan2(ay, az)
      * 180.0 / PI;

  float accelPitch =
      atan2(
        -ax,
        sqrt(ay * ay + az * az)
      )
      * 180.0 / PI;


  // =================================================
  // GYROSCOPE ANGLES
  // =================================================

  gyroRoll += gx * dt;
  gyroPitch += gy * dt;
  gyroYaw += gz * dt;


  // =================================================
  // SERIAL MONITOR
  // =================================================

  Serial.print("ACC: ");

  Serial.print("X=");
  Serial.print(ax_g, 2);

  Serial.print("g  Y=");
  Serial.print(ay_g, 2);

  Serial.print("g  Z=");
  Serial.print(az_g, 2);

  Serial.print("g");


  // Accelerometer angles

  Serial.print("  |  ACC ANGLE: ");

  Serial.print("Pitch=");
  Serial.print(accelPitch, 1);

  Serial.print("°  Roll=");
  Serial.print(accelRoll, 1);

  Serial.print("°");


  // Gyroscope angular velocity

  Serial.print("  |  GYRO: ");

  Serial.print("X=");
  Serial.print(gx, 2);

  Serial.print("°/s  Y=");
  Serial.print(gy, 2);

  Serial.print("°/s  Z=");
  Serial.print(gz, 2);

  Serial.print("°/s");


  // Gyroscope-integrated angles

  Serial.print("  |  GYRO ANGLE: ");

  Serial.print("Pitch=");
  Serial.print(gyroPitch, 1);

  Serial.print("°  Roll=");
  Serial.print(gyroRoll, 1);

  Serial.print("°  Yaw=");
  Serial.print(gyroYaw, 1);

  Serial.println("°");


  delay(20);
}