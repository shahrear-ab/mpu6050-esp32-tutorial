# MPU6050 + ESP32 Tutorial

A practical tutorial project demonstrating how to use the **MPU6050 6-axis IMU** with an **ESP32**.

This project covers the fundamentals of accelerometers and gyroscopes, tilt-angle calculation, gyroscope integration, gyroscope calibration, and a motion-intensity LED indicator.

> 🎥 This project is part of a robotics and electronics tutorial by **Roborear**.

---

## 📌 What You'll Learn

In this project, you will learn how to:

- Interface an MPU6050 with an ESP32
- Read 3-axis accelerometer data
- Read 3-axis gyroscope data
- Understand how an accelerometer works
- Understand how a MEMS gyroscope works
- Calculate pitch and roll using acceleration due to gravity
- Calculate angular displacement by integrating gyroscope data
- Calibrate gyroscope bias
- Understand gyroscope drift
- Detect motion intensity
- Control LEDs based on motion intensity
- Use the Adafruit MPU6050 library

---

## 🧠 About the MPU6050

The **MPU6050** is a 6-axis Inertial Measurement Unit (IMU).

It contains:

- **3-axis accelerometer**
  - X-axis
  - Y-axis
  - Z-axis

- **3-axis gyroscope**
  - X-axis
  - Y-axis
  - Z-axis

Therefore:

```text
3-axis Accelerometer
        +
3-axis Gyroscope
        =
6-axis IMU
```

# MPU6050 + ESP32 Tutorial

A practical ESP32 project demonstrating the **MPU6050 6-axis IMU**, including accelerometer readings, gyroscope readings, tilt estimation, gyro integration, calibration, and motion detection using LEDs.

## 📌 Features

- 3-axis accelerometer readings
- 3-axis gyroscope readings
- Pitch and roll estimation using gravity
- Gyroscope angle integration
- Gyroscope bias calibration
- Motion-intensity LED indicator
- ESP32 I²C communication

---

## 🔧 Hardware

- ESP32 development board
- MPU6050 module
- Blue, Green & Red LEDs
- 3 × 337 Ω resistors
- Breadboard
- Jumper wires

---

## 🔌 Wiring

### MPU6050 → ESP32

| MPU6050 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

### LEDs → ESP32

| LED | GPIO | Resistor |
|---|---:|---:|
| 🔵 Blue | GPIO 13 | 337 Ω |
| 🟢 Green | GPIO 14 | 337 Ω |
| 🔴 Red | GPIO 26 | 337 Ω |

Connect each LED in series with its resistor to GND.

---

## 📁 Project Structure

```text
mpu6050-esp32-tutorial/
│
├── README.md
├── LICENSE
│
├── code/
│   ├── mpu6050_accelerometer_gyroscope/
│   │   └── mpu6050_accelerometer_gyroscope.ino
│   │
│   └── mpu6050_motion_led/
│       └── mpu6050_motion_led.ino
