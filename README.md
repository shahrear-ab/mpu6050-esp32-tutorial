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
